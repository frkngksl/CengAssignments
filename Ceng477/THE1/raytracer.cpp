#include <iostream>
#include <cmath>
#include <cfloat>
#include <bits/stdc++.h>
#include <thread>
#include "parser.h"
#include "ppm.h"
#define MESH 0
#define TRIANGLE 1
#define SPHERE 2
#define BACKGROUND 3

typedef unsigned char RGB[3];

typedef struct{
	parser::Vec3f parameterConstant;
	parser::Vec3f parameterCoefficient;
} Ray;

double insideTriangleTest(Ray givenRay,parser::Vec3f vertex0,parser::Vec3f vertex1, parser::Vec3f vertex2){
	double beta,gamma,returningValue;
	double a,b,c,d,e,f,g,h,i,j,k,l;
	double eimhf,gfmdi,dhmeg,akmjb,jcmal,blmkc;
	double determinantA;
	a = vertex0.x-vertex1.x;
	b = vertex0.y-vertex1.y;
	c = vertex0.z-vertex1.z;

	d = vertex0.x-vertex2.x;
	e = vertex0.y-vertex2.y;
	f = vertex0.z-vertex2.z;

	g = givenRay.parameterCoefficient.x;
	h = givenRay.parameterCoefficient.y;
	i = givenRay.parameterCoefficient.z;

	j = vertex0.x-givenRay.parameterConstant.x;
	k = vertex0.y-givenRay.parameterConstant.y;
	l = vertex0.z-givenRay.parameterConstant.z;

	eimhf = e*i-h*f;
	gfmdi = g*f-d*i;
	dhmeg = d*h-e*g;
	akmjb = a*k-j*b;
	jcmal = j*c-a*l;
	blmkc = b*l-k*c;

	determinantA = a*eimhf+b*gfmdi+c*dhmeg;
	if(determinantA == 0){
		return -1;
	}
	returningValue = -(f*akmjb+e*jcmal+d*blmkc)/determinantA;

	gamma = (i*akmjb+h*jcmal+g*blmkc)/determinantA;

	if (gamma<0|| gamma>1){
		return -1;
	}

	beta = (j*eimhf+k*gfmdi+l*dhmeg)/determinantA;

	if (beta < 0 || beta>(1-gamma)){
		return -1;
	}

	return returningValue;

}

Ray generateRay(parser::Vec3f camPosition,parser::Vec3f topLeft,parser::Vec3f upVector,parser::Vec3f rightVector,int currentPixelX,int currentPixelY,double pixelWidth,double pixelHeight){
    Ray returningValue = {0,0};
    parser::Vec3f tmpS = {0,0,0};
    returningValue.parameterConstant = camPosition;
    double su = (currentPixelX+0.5)*pixelWidth;
    double sv = (currentPixelY+0.5)*pixelHeight;

    tmpS.x = su*rightVector.x-sv*upVector.x+topLeft.x;
    tmpS.y = su*rightVector.y-sv*upVector.y+topLeft.y;
    tmpS.z = su*rightVector.z-sv*upVector.z+topLeft.z;

    returningValue.parameterCoefficient.x = tmpS.x-camPosition.x;
    returningValue.parameterCoefficient.y = tmpS.y-camPosition.y;
    returningValue.parameterCoefficient.z = tmpS.z-camPosition.z;

    return returningValue;
}

double innerProduct(parser::Vec3f a, parser::Vec3f b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

parser::Vec3f scalarProduct(parser::Vec3f a,double product){
    parser::Vec3f returningValue = {0,0,0};

    returningValue.x = product * a.x;
    returningValue.y = product * a.y;
    returningValue.z = product * a.z;

    return returningValue;
}

parser::Vec3f crossProduct(parser::Vec3f a, parser::Vec3f b)
{
	parser::Vec3f returningValue = {0,0,0};

	returningValue.x = a.y*b.z-b.y*a.z;
	returningValue.y = b.x*a.z-a.x*b.z;
	returningValue.z = a.x*b.y-b.x*a.y;

	return returningValue;
}

double lengthOfVector(parser::Vec3f v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

parser::Vec3f normalize(parser::Vec3f v){
	parser::Vec3f returningValue = {0,0,0};
	double length;
	length=lengthOfVector(v);
    if(fabs(length-1.0) > 0.0001){
        returningValue.x = v.x/length;
        returningValue.y = v.y/length;
        returningValue.z = v.z/length;
    }
    else{
        returningValue = v;
    }
	return returningValue;
}

double checkTrianglesIntersection(Ray givenRay,parser::Scene &sceneGiven,parser::Triangle givenTriangle){
	//first check plane intersection
	parser::Vec3f vertex0;
	parser::Vec3f vertex1;
	parser::Vec3f vertex2;
	parser::Vec3f temp;
	double dn = innerProduct(givenRay.parameterCoefficient,givenTriangle.normalVector);
	double returningValue;
	if(dn != 0){
		vertex0 = sceneGiven.vertex_data[givenTriangle.indices.v0_id-1];
		vertex1 = sceneGiven.vertex_data[givenTriangle.indices.v1_id-1];
		vertex2 = sceneGiven.vertex_data[givenTriangle.indices.v2_id-1];

		returningValue = insideTriangleTest(givenRay,vertex0,vertex1,vertex2);
	/*
		temp.x = vertex0.x - givenRay.parameterConstant.x;
		temp.y = vertex0.y - givenRay.parameterConstant.y;
		temp.z = vertex0.z - givenRay.parameterConstant.z;

		returningValue = innerProduct(temp,givenTriangle.normalVector)/dn;
		if(returningValue > currentTValue){
			returningValue = -1;
		}
		else{
			parser::Vec3f rayIntersectionPoint;
			parser::Vec3f tempForCoeff = scalarProduct(givenRay.parameterCoefficient,returningValue);
			rayIntersectionPoint.x = tempForCoeff.x + givenRay.parameterConstant.x;
			rayIntersectionPoint.y = tempForCoeff.y + givenRay.parameterConstant.y;
			rayIntersectionPoint.z = tempForCoeff.z + givenRay.parameterConstant.z;
			insideTriangleTest(rayIntersectionPoint,vertex0,vertex1,vertex2);
		}
	*/
	}
	else{
		returningValue = -1;
	}
	return returningValue;
}

double checkMeshIntersection(Ray givenRay,parser::Scene &sceneGiven,parser::Face givenFace,parser::Vec3f normalVector){
	parser::Vec3f vertex0;
	parser::Vec3f vertex1;
	parser::Vec3f vertex2;
	parser::Vec3f temp;
	double dn = innerProduct(givenRay.parameterCoefficient,normalVector);
	double returningValue;
	if(dn != 0){
		vertex0 = sceneGiven.vertex_data[givenFace.v0_id-1];
		vertex1 = sceneGiven.vertex_data[givenFace.v1_id-1];
		vertex2 = sceneGiven.vertex_data[givenFace.v2_id-1];
		returningValue = insideTriangleTest(givenRay,vertex0,vertex1,vertex2);
	}
	else{
		returningValue = -1;
	}
	return returningValue;
}



double checkSphereIntersection(Ray givenRay,parser::Sphere givenSphere,parser::Vec3f centerVertexCoord,double ddResult){
	double returningValue ;
	double equationA = ddResult;
    parser::Vec3f tmpForB;
    tmpForB.x = givenRay.parameterConstant.x-centerVertexCoord.x;
    tmpForB.y = givenRay.parameterConstant.y-centerVertexCoord.y;
    tmpForB.z = givenRay.parameterConstant.z-centerVertexCoord.z;
    double equationB = innerProduct(scalarProduct(givenRay.parameterCoefficient,2),tmpForB);
    double equationC = innerProduct(tmpForB,tmpForB)-(givenSphere.radius*givenSphere.radius);
    //At^2+Bt+C=0
    double discriminantValue = sqrt(equationB*equationB-4*equationA*equationC);
	if(discriminantValue<0){ //TODO
		returningValue = -1;
	}
	else{
		double t1 = (-equationB+sqrt(equationB*equationB-4*equationA*equationC))/(2*equationA);
		double t2 = (-equationB-sqrt(equationB*equationB-4*equationA*equationC))/(2*equationA);
		//std::cout << t1 << t2 << std::endl;
		//TODO: Biri negatif, biri pozitif ?
		if(t1 < t2){
			returningValue = t1;
		}
		else{
			returningValue = t2;
		}
	}
    return returningValue;
}

void calculateNormalVectors(parser::Scene &sceneGiven){
	parser::Vec3f vertex0;
	parser::Vec3f vertex1;
	parser::Vec3f vertex2;
	parser::Vec3f temp1;
	parser::Vec3f temp2;
	parser::Vec3f normalTemp;
	size_t triangleSize = sceneGiven.triangles.size();
	size_t meshSize = sceneGiven.meshes.size();
	size_t triangleMeshSize;
	for(int i=0;i<triangleSize;i++){
		vertex0 = sceneGiven.vertex_data[sceneGiven.triangles[i].indices.v0_id-1];
		vertex1 = sceneGiven.vertex_data[sceneGiven.triangles[i].indices.v1_id-1];
		vertex2 = sceneGiven.vertex_data[sceneGiven.triangles[i].indices.v2_id-1];

		temp1.x = vertex1.x-vertex0.x;
		temp1.y = vertex1.y-vertex0.y;
		temp1.z = vertex1.z-vertex0.z;

		temp2.x = vertex2.x-vertex0.x;
		temp2.y = vertex2.y-vertex0.y;
		temp2.z = vertex2.z-vertex0.z;

		normalTemp = crossProduct(temp1,temp2);
		normalTemp = normalize(normalTemp);
		sceneGiven.triangles[i].normalVector = normalTemp;
	}
	for(int i=0;i<meshSize;i++){
		triangleMeshSize = sceneGiven.meshes[i].faces.size();
		for(int j=0;j<triangleMeshSize;j++){
			vertex0 = sceneGiven.vertex_data[sceneGiven.meshes[i].faces[j].v0_id-1];
			vertex1 = sceneGiven.vertex_data[sceneGiven.meshes[i].faces[j].v1_id-1];
			vertex2 = sceneGiven.vertex_data[sceneGiven.meshes[i].faces[j].v2_id-1];

			temp1.x = vertex1.x-vertex0.x;
			temp1.y = vertex1.y-vertex0.y;
			temp1.z = vertex1.z-vertex0.z;

			temp2.x = vertex2.x-vertex0.x;
			temp2.y = vertex2.y-vertex0.y;
			temp2.z = vertex2.z-vertex0.z;

			normalTemp = crossProduct(temp1,temp2);
			normalTemp = normalize(normalTemp);
			sceneGiven.meshes[i].normalVectors.push_back(normalTemp);
		}
	}
    /*for(int i=0;i<sceneGiven.spheres.size();i++){
        calculateNormalOfSphere(sceneGiven.spheres[i]);
    }*/
}

bool shadowTest(parser::Scene &sceneGiven,parser::PointLight lightGiven,parser::Vec3f givenPoint){

	Ray shadowRay = {0,0};
	double temp;
	double ddResult;
	size_t sphereSize = sceneGiven.spheres.size();
	size_t triangleSize = sceneGiven.triangles.size();
	size_t meshSize = sceneGiven.meshes.size();
	size_t triangleMeshSize;
	size_t lightSourceSize = sceneGiven.point_lights.size();
	double distanceForT;
	parser::Vec3f vectorWi;
	vectorWi.x = lightGiven.position.x - givenPoint.x;
	vectorWi.y = lightGiven.position.y - givenPoint.y;
	vectorWi.z = lightGiven.position.z - givenPoint.z;
	parser::Vec3f normalizeHal = normalize(vectorWi);
	distanceForT = lengthOfVector(vectorWi);
	shadowRay.parameterConstant.x = givenPoint.x+(normalizeHal.x*sceneGiven.shadow_ray_epsilon);
	shadowRay.parameterConstant.y = givenPoint.y+(normalizeHal.y*sceneGiven.shadow_ray_epsilon);
	shadowRay.parameterConstant.z = givenPoint.z+(normalizeHal.z*sceneGiven.shadow_ray_epsilon);

	shadowRay.parameterCoefficient.x = normalizeHal.x;
	shadowRay.parameterCoefficient.y = normalizeHal.y;
	shadowRay.parameterCoefficient.z = normalizeHal.z;
	ddResult = innerProduct(shadowRay.parameterCoefficient,shadowRay.parameterCoefficient);
	for(int i=0;i<sphereSize;i++){
		temp = checkSphereIntersection(shadowRay,sceneGiven.spheres[i],sceneGiven.vertex_data[sceneGiven.spheres[i].center_vertex_id-1],ddResult);
		//std::cout<<"Temp:"<<temp<<std::endl;
		if(temp >= 0 && temp< distanceForT){
			return true;
		}
	}
	for(int i=0;i<triangleSize;i++){
		temp = checkTrianglesIntersection(shadowRay,sceneGiven,sceneGiven.triangles[i]);
		if(temp >=0 && temp < distanceForT){
			return true;
		}
	}
	for(int i=0;i<meshSize;i++){
		triangleMeshSize = sceneGiven.meshes[i].faces.size();
		for(int j=0;j<triangleMeshSize;j++){
			temp = checkMeshIntersection(shadowRay,sceneGiven,sceneGiven.meshes[i].faces[j],sceneGiven.meshes[i].normalVectors[j]);
			//std::cout << "TempMesh: "<< temp << "Shadow:"<< shadowRay.parameterCoefficient.x << " "<< shadowRay.parameterCoefficient.y << " "<< shadowRay.parameterCoefficient.z<<std::endl;
			if(temp >= 0 && temp < distanceForT){
				return true;
			}
		}
	}
	return false;
}

parser::Vec3i specularShadingCalculator(parser::PointLight lightGiven,parser::Vec3f givenNormal,parser::Vec3f givenPoint,parser::Vec3f cameraPosition,parser::Vec3f specularReflectanceCoefficient,double phongExponent){
	parser::Vec3i returningColor = {0};
	parser::Vec3f vectorWi = {0};
	parser::Vec3f vectorWo = {0};
	parser::Vec3f halfVector = {0};
	parser::Vec3i newIntensity = {0};
	double distance = 0;
	double cosTheta = 0;
	vectorWi.x = lightGiven.position.x - givenPoint.x;
	vectorWi.y = lightGiven.position.y - givenPoint.y;
	vectorWi.z = lightGiven.position.z - givenPoint.z;
	distance = lengthOfVector(vectorWi);
	vectorWi = normalize(vectorWi);
	vectorWo.x = cameraPosition.x - givenPoint.x;
	vectorWo.y = cameraPosition.y - givenPoint.y;
	vectorWo.z = cameraPosition.z - givenPoint.z;
	vectorWo = normalize(vectorWo);
	halfVector.x = vectorWi.x + vectorWo.x;
	halfVector.y = vectorWi.y + vectorWo.y;
	halfVector.z = vectorWi.z + vectorWo.z;
	halfVector = normalize(halfVector);
	cosTheta = innerProduct(givenNormal,halfVector);
	if(cosTheta < 0){
		cosTheta = 0;
	}
	cosTheta = pow(cosTheta,phongExponent);
	newIntensity.x = lightGiven.intensity.x/(distance*distance);
	newIntensity.y = lightGiven.intensity.y/(distance*distance);
	newIntensity.z = lightGiven.intensity.z/(distance*distance);
	returningColor.x = specularReflectanceCoefficient.x*cosTheta*newIntensity.x;
	returningColor.y = specularReflectanceCoefficient.y*cosTheta*newIntensity.y;
	returningColor.z = specularReflectanceCoefficient.z*cosTheta*newIntensity.z;
	return returningColor;

}

parser::Vec3i diffuseShadingCalculator(parser::PointLight lightGiven,parser::Vec3f givenNormal,parser::Vec3f givenPoint,parser::Vec3f diffuseReflectanceCoefficient){
	parser::Vec3i returningColor;
	parser::Vec3f vectorWi;
	parser::Vec3i newIntensity;
	double distance;
	double cosTheta;
	vectorWi.x = lightGiven.position.x - givenPoint.x;
	vectorWi.y = lightGiven.position.y - givenPoint.y;
	vectorWi.z = lightGiven.position.z - givenPoint.z;
	distance = lengthOfVector(vectorWi);
	vectorWi = normalize(vectorWi);
	cosTheta = innerProduct(vectorWi,givenNormal);
	if(cosTheta<0){
		cosTheta = 0;
	}
	newIntensity.x = lightGiven.intensity.x/(distance*distance);
	newIntensity.y = lightGiven.intensity.y/(distance*distance);
	newIntensity.z = lightGiven.intensity.z/(distance*distance);
	returningColor.x = diffuseReflectanceCoefficient.x*cosTheta*newIntensity.x;
	returningColor.y = diffuseReflectanceCoefficient.y*cosTheta*newIntensity.y;
	returningColor.z = diffuseReflectanceCoefficient.z*cosTheta*newIntensity.z;
	return returningColor;
}

parser::Vec3i getColorFromRay(Ray givenRay,parser::Scene &sceneGiven,parser::Vec3f cameraPosition,int recursionNumber){
    double tmin = DBL_MAX;
    double temp = 0;
	long indexOfObject =0;
	long indexOfFace =0 ;
	parser::Material objectProperties ={0};
	int chosenObjectType = BACKGROUND;
    double ddResult = innerProduct(givenRay.parameterCoefficient,givenRay.parameterCoefficient);
	unsigned int sphereSize = sceneGiven.spheres.size();
	unsigned int triangleSize = sceneGiven.triangles.size();
	unsigned int meshSize = sceneGiven.meshes.size();
	unsigned int triangleMeshSize = 0;
	unsigned int lightSourceSize = sceneGiven.point_lights.size();
	parser::Vec3i returningColor = {0,0,0};
	double pixelValuex = 0;
	double pixelValuey = 0 ;
	double pixelValuez = 0;
	parser::Vec3i reflectedCame = {0,0,0};
    for(int i=0;i<sphereSize;i++){
        temp = checkSphereIntersection(givenRay,sceneGiven.spheres[i],sceneGiven.vertex_data[sceneGiven.spheres[i].center_vertex_id-1],ddResult);
		if(temp > 0.0001){
			if(temp < tmin){
				tmin = temp;
				indexOfObject = i;
				chosenObjectType = SPHERE;
			}
		}
    }
	for(int i=0;i<triangleSize;i++){
		temp = checkTrianglesIntersection(givenRay,sceneGiven,sceneGiven.triangles[i]);
		if(temp > 0.0001){
			if(temp < tmin){
				tmin = temp;
				indexOfObject = i;
				chosenObjectType = TRIANGLE;
			}
		}
	}
	for(int i=0;i<meshSize;i++){
		triangleMeshSize = sceneGiven.meshes[i].faces.size();
		for(int j=0;j<triangleMeshSize;j++){
			temp = checkMeshIntersection(givenRay,sceneGiven,sceneGiven.meshes[i].faces[j],sceneGiven.meshes[i].normalVectors[j]);
			if(temp > 0.0001){
				if(temp < tmin){
					tmin = temp;
					indexOfObject = i;
					indexOfFace = j;
					chosenObjectType = MESH;
				}
			}
		}
	}
	if(chosenObjectType == BACKGROUND){
		returningColor.x = 0;
		returningColor.y = 0;
		returningColor.z = 0;
		returningColor.x = sceneGiven.background_color.x;
		returningColor.y = sceneGiven.background_color.y;
		returningColor.z = sceneGiven.background_color.z;
	}
	else{
		parser::Vec3f currentPoint;
		parser::Vec3i tmpColor;
		currentPoint.x = givenRay.parameterConstant.x + givenRay.parameterCoefficient.x*tmin;
		currentPoint.y = givenRay.parameterConstant.y + givenRay.parameterCoefficient.y*tmin;
		currentPoint.z = givenRay.parameterConstant.z + givenRay.parameterCoefficient.z*tmin;
		returningColor.x = 0;
		returningColor.y = 0;
		returningColor.z = 0;
		if(chosenObjectType == MESH){
			//return {255,255,255};
			objectProperties = sceneGiven.materials[sceneGiven.meshes[indexOfObject].material_id-1];
			for(int i=0;i<lightSourceSize;i++){
				if(shadowTest(sceneGiven,sceneGiven.point_lights[i],currentPoint)){
					//std::cout << "GİRDİ" << std::endl;
					continue;
				}
				tmpColor = diffuseShadingCalculator(sceneGiven.point_lights[i],sceneGiven.meshes[indexOfObject].normalVectors[indexOfFace],currentPoint,objectProperties.diffuse);
				returningColor.x+=tmpColor.x;
				returningColor.y+=tmpColor.y;
				returningColor.z+=tmpColor.z;
				tmpColor = specularShadingCalculator(sceneGiven.point_lights[i],sceneGiven.meshes[indexOfObject].normalVectors[indexOfFace],currentPoint,cameraPosition,objectProperties.specular,objectProperties.phong_exponent);
				returningColor.x+=tmpColor.x;
				returningColor.y+=tmpColor.y;
				returningColor.z+=tmpColor.z;
			}
			returningColor.x= returningColor.x+(objectProperties.ambient.x*sceneGiven.ambient_light.x);
			returningColor.y= returningColor.y+(objectProperties.ambient.y*sceneGiven.ambient_light.y);
			returningColor.z= returningColor.z+(objectProperties.ambient.z*sceneGiven.ambient_light.z);
			//std::cout << "Mesh Mirror: " << objectProperties.mirror.x << " " << objectProperties.mirror.y << " " << objectProperties.mirror.z << std::endl;
			if(objectProperties.mirror.x != 0 || objectProperties.mirror.y != 0 || objectProperties.mirror.z != 0){
				if(recursionNumber != sceneGiven.max_recursion_depth){
					//std::cout << "Mesh Ama girdi" << std::endl;
					Ray newRay;
					double intermediateResult;
					parser::Vec3f vectorWo;
					parser::Vec3f normalVect;
					parser::Vec3f tempVect;
					parser::Vec3f vectorWr;
					parser::Vec3i resultFromReflect;
					normalVect.x = sceneGiven.meshes[indexOfObject].normalVectors[indexOfFace].x;
					normalVect.y = sceneGiven.meshes[indexOfObject].normalVectors[indexOfFace].y;
					normalVect.z = sceneGiven.meshes[indexOfObject].normalVectors[indexOfFace].z;
					vectorWo.x = cameraPosition.x - currentPoint.x;
					vectorWo.y = cameraPosition.y - currentPoint.y;
					vectorWo.z = cameraPosition.z - currentPoint.z;
					vectorWo = normalize(vectorWo);
					intermediateResult = innerProduct(normalVect,vectorWo);
					tempVect = scalarProduct(normalVect,2*intermediateResult);
					vectorWr.x = tempVect.x-vectorWo.x;
					vectorWr.y = tempVect.y-vectorWo.y;
					vectorWr.z = tempVect.z-vectorWo.z;
					vectorWr = normalize(vectorWr);
					newRay.parameterConstant.x = currentPoint.x;
					newRay.parameterConstant.y = currentPoint.y;
					newRay.parameterConstant.z = currentPoint.z;
					newRay.parameterCoefficient.x = vectorWr.x;
					newRay.parameterCoefficient.y = vectorWr.y;
					newRay.parameterCoefficient.z = vectorWr.z;
					resultFromReflect = getColorFromRay(newRay,sceneGiven,currentPoint,recursionNumber+1);
					returningColor.x+=(objectProperties.mirror.x*resultFromReflect.x);
					returningColor.y+=(objectProperties.mirror.y*resultFromReflect.y);
					returningColor.z+=(objectProperties.mirror.z*resultFromReflect.z);
				}
			}
		}
		else if(chosenObjectType == TRIANGLE){
			//return {255,255,255};
			objectProperties = sceneGiven.materials[sceneGiven.triangles[indexOfObject].material_id-1];
			for(int i=0;i<lightSourceSize;i++){
				if(shadowTest(sceneGiven,sceneGiven.point_lights[i],currentPoint)){
					//std::cout << "GİRDİ" << std::endl;
					continue;
				}
				tmpColor = diffuseShadingCalculator(sceneGiven.point_lights[i],sceneGiven.triangles[indexOfObject].normalVector,currentPoint,objectProperties.diffuse);
				returningColor.x+=tmpColor.x;
				returningColor.y+=tmpColor.y;
				returningColor.z+=tmpColor.z;
				tmpColor = specularShadingCalculator(sceneGiven.point_lights[i],sceneGiven.triangles[indexOfObject].normalVector,currentPoint,cameraPosition,objectProperties.specular,objectProperties.phong_exponent);
				returningColor.x+=tmpColor.x;
				returningColor.y+=tmpColor.y;
				returningColor.z+=tmpColor.z;
			}
			returningColor.x= returningColor.x+(objectProperties.ambient.x*sceneGiven.ambient_light.x);
			returningColor.y= returningColor.y+(objectProperties.ambient.y*sceneGiven.ambient_light.y);
			returningColor.z= returningColor.z+(objectProperties.ambient.z*sceneGiven.ambient_light.z);
			//std::cout << "Triangle Mirror: " << objectProperties.mirror.x << " " << objectProperties.mirror.y << " " << objectProperties.mirror.z << std::endl;
			if(objectProperties.mirror.x != 0 || objectProperties.mirror.y != 0 || objectProperties.mirror.z != 0){
				if(recursionNumber != sceneGiven.max_recursion_depth){
					//std::cout << "Triangle ama girdi "<< std::endl;
					Ray newRay;
					double intermediateResult;
					parser::Vec3f vectorWo;
					parser::Vec3f normalVect;
					parser::Vec3f tempVect;
					parser::Vec3f vectorWr;
					parser::Vec3i resultFromReflect;
					normalVect.x = sceneGiven.triangles[indexOfObject].normalVector.x;
					normalVect.y = sceneGiven.triangles[indexOfObject].normalVector.y;
					normalVect.z = sceneGiven.triangles[indexOfObject].normalVector.z;
					vectorWo.x = cameraPosition.x - currentPoint.x;
					vectorWo.y = cameraPosition.y - currentPoint.y;
					vectorWo.z = cameraPosition.z - currentPoint.z;
					vectorWo = normalize(vectorWo);
					intermediateResult = innerProduct(normalVect,vectorWo);
					tempVect = scalarProduct(normalVect,2*intermediateResult);
					vectorWr.x = tempVect.x-vectorWo.x;
					vectorWr.y = tempVect.y-vectorWo.y;
					vectorWr.z = tempVect.z-vectorWo.z;
					vectorWr = normalize(vectorWr);
					newRay.parameterConstant.x = currentPoint.x;
					newRay.parameterConstant.y = currentPoint.y;
					newRay.parameterConstant.z = currentPoint.z;
					newRay.parameterCoefficient.x = vectorWr.x;
					newRay.parameterCoefficient.y = vectorWr.y;
					newRay.parameterCoefficient.z = vectorWr.z;
					resultFromReflect = getColorFromRay(newRay,sceneGiven,currentPoint,recursionNumber+1);
					returningColor.x+=(objectProperties.mirror.x*resultFromReflect.x);
					returningColor.y+=(objectProperties.mirror.y*resultFromReflect.y);
					returningColor.z+=(objectProperties.mirror.z*resultFromReflect.z);
				}
			}
		}
		else if(chosenObjectType == SPHERE){
			//return {255,255,255};
			parser::Vec3f normalVectorForSphere;
			parser::Vec3f centerPoint = sceneGiven.vertex_data[sceneGiven.spheres[indexOfObject].center_vertex_id-1];
			normalVectorForSphere.x = currentPoint.x - centerPoint.x;
			normalVectorForSphere.y = currentPoint.y - centerPoint.y;
			normalVectorForSphere.z = currentPoint.z - centerPoint.z;
			normalVectorForSphere = normalize(normalVectorForSphere);
			objectProperties = sceneGiven.materials[sceneGiven.spheres[indexOfObject].material_id-1];
			for(int i=0;i<lightSourceSize;i++){
				if(shadowTest(sceneGiven,sceneGiven.point_lights[i],currentPoint)){
					//std::cout << "GİRDİ" << std::endl;
					continue;
				}
				tmpColor = diffuseShadingCalculator(sceneGiven.point_lights[i],normalVectorForSphere,currentPoint,objectProperties.diffuse);
				returningColor.x+=tmpColor.x;
				returningColor.y+=tmpColor.y;
				returningColor.z+=tmpColor.z;
				tmpColor = specularShadingCalculator(sceneGiven.point_lights[i],normalVectorForSphere,currentPoint,cameraPosition,objectProperties.specular,objectProperties.phong_exponent);
				returningColor.x+=tmpColor.x;
				returningColor.y+=tmpColor.y;
				returningColor.z+=tmpColor.z;
			}
			returningColor.x= returningColor.x+(objectProperties.ambient.x*sceneGiven.ambient_light.x);
			returningColor.y= returningColor.y+(objectProperties.ambient.y*sceneGiven.ambient_light.y);
			returningColor.z= returningColor.z+(objectProperties.ambient.z*sceneGiven.ambient_light.z);
			//std::cout << "Sphere Mirror: " << objectProperties.mirror.x << " " << objectProperties.mirror.y << " " << objectProperties.mirror.z << std::endl;
			if(objectProperties.mirror.x != 0 || objectProperties.mirror.y != 0 || objectProperties.mirror.z != 0){
				if(recursionNumber != sceneGiven.max_recursion_depth){
					//std::cout << "Sphere ama girdi" << std::endl;
					Ray newRay;
					double intermediateResult;
					parser::Vec3f vectorWo;
					parser::Vec3f normalVect = normalVectorForSphere;
					parser::Vec3f tempVect;
					parser::Vec3f vectorWr;
					parser::Vec3i resultFromReflect;
					vectorWo.x = cameraPosition.x - currentPoint.x;
					vectorWo.y = cameraPosition.y - currentPoint.y;
					vectorWo.z = cameraPosition.z - currentPoint.z;
					vectorWo = normalize(vectorWo);
					intermediateResult = innerProduct(normalVect,vectorWo);
					tempVect = scalarProduct(normalVect,2*intermediateResult);
					normalVect.x = normalVectorForSphere.x;
					normalVect.y = normalVectorForSphere.y;
					normalVect.z = normalVectorForSphere.z;
					vectorWr.x = tempVect.x-vectorWo.x;
					vectorWr.y = tempVect.y-vectorWo.y;
					vectorWr.z = tempVect.z-vectorWo.z;
					vectorWr = normalize(vectorWr);
					newRay.parameterConstant.x = currentPoint.x;
					newRay.parameterConstant.y = currentPoint.y;
					newRay.parameterConstant.z = currentPoint.z;
					newRay.parameterCoefficient.x = vectorWr.x;
					newRay.parameterCoefficient.y = vectorWr.y;
					newRay.parameterCoefficient.z = vectorWr.z;
					resultFromReflect = getColorFromRay(newRay,sceneGiven,currentPoint,recursionNumber+1);
					returningColor.x+=(objectProperties.mirror.x*resultFromReflect.x);
					returningColor.y+=(objectProperties.mirror.y*resultFromReflect.y);
					returningColor.z+=(objectProperties.mirror.z*resultFromReflect.z);
				}
			}
		}

	}
	return returningColor;
}

void startThreadFor(int loopCount,int startHeight,int totalWidth,unsigned char *imagePlane,parser::Vec3f topLeftPointQ,
	double pixelWidth,double pixelHeight,parser::Scene scene,int cameraCounter){
	parser::Vec3i tmpColor;
	int araci;
	unsigned char pixelColor[3];
	parser::Vec3f cameraPosition = scene.cameras[cameraCounter].position;
	parser::Vec3f cameraUp = normalize(scene.cameras[cameraCounter].up);
	parser::Vec3f cameraGaze = normalize(scene.cameras[cameraCounter].gaze);
	parser::Vec3f cameraRight = normalize(crossProduct(cameraGaze,cameraUp));
	double cameraDistance = scene.cameras[cameraCounter].near_distance;
	int pixelCounter = 0;
	Ray currentPrimaryRay;
	for(int y=0;y<startHeight;++y){
		for (int x = 0; x < totalWidth; ++x){
			pixelCounter++;
			pixelCounter++;
			pixelCounter++;
		}
	}
	for (int y = startHeight; y < (startHeight+loopCount); ++y){
		for (int x = 0; x < totalWidth; ++x){
			currentPrimaryRay = generateRay(cameraPosition,topLeftPointQ,cameraUp,cameraRight,x,y,pixelWidth,pixelHeight);
			//std::cout << "Primary ray" << currentPrimaryRay.parameterConstant.x<<currentPrimaryRay.parameterConstant.y  << currentPrimaryRay.parameterCoefficient.x << currentPrimaryRay.parameterConstant.y << std::endl;
			tmpColor = getColorFromRay(currentPrimaryRay,scene,scene.cameras[cameraCounter].position,0);
			tmpColor.x = round(tmpColor.x);
			tmpColor.y = round(tmpColor.y);
			tmpColor.z = round(tmpColor.z);

			if(tmpColor.x>255){
				pixelColor[0] = 255;
			}
			else{
				araci = tmpColor.x;
				pixelColor[0] = araci;
			}
			if(tmpColor.y>255){
				pixelColor[1] = 255;
			}
			else{
				araci = tmpColor.y;
				pixelColor[1] = araci;
			}
			if(tmpColor.z>255){
				pixelColor[2] = 255;
			}
			else{
				araci = tmpColor.z;
				pixelColor[2] = araci;
			}
			imagePlane[pixelCounter++] = pixelColor[0];
			imagePlane[pixelCounter++] = pixelColor[1];
			imagePlane[pixelCounter++] = pixelColor[2];
		}
	}
}


int main(int argc, char* argv[])
{
    // Sample usage for reading an XML scene file
    parser::Scene scene;

    int width;
    int height;

    int pixelCounter;

    double left;
    double right;
    double top;
    double bottom;

    parser::Vec3f cameraPosition;
    parser::Vec3f cameraGaze;
    parser::Vec3f cameraUp;
    parser::Vec3f cameraRight;
    parser::Vec3f cameraReferencePointM;
    parser::Vec3f topLeftPointQ;
    double cameraDistance;

    double pixelWidth;
    double pixelHeight;

    Ray currentPrimaryRay;
    std::string imageOutputNameStr;
	char* imageOutputName;
    unsigned char *imagePlane;
    scene.loadFromXml(argv[1]);
	unsigned char pixelColor[3];
	parser::Vec3i tmpColor;
	int threadSharingHowMany;
	int threadSharingLast;
	int araci;
    calculateNormalVectors(scene);
	size_t cameraSize = scene.cameras.size();
    for(int cameraCounter = 0; cameraCounter<cameraSize; cameraCounter++){
        width = scene.cameras[cameraCounter].image_width;
        height = scene.cameras[cameraCounter].image_height;

        imageOutputNameStr = scene.cameras[cameraCounter].image_name;
		int n = imageOutputNameStr.length();

    	// declaring character array
    	imageOutputName = new char[imageOutputNameStr.length()+1];
		imageOutputName[imageOutputNameStr.length()] = '\0';

    	// copying the contents of the
	    // string to char array
    	strcpy(imageOutputName, imageOutputNameStr.c_str());
        imagePlane = new unsigned char [width * height * 3];

        left = scene.cameras[cameraCounter].near_plane.x;
        right = scene.cameras[cameraCounter].near_plane.y;
        bottom = scene.cameras[cameraCounter].near_plane.z;
        top = scene.cameras[cameraCounter].near_plane.w;

        cameraPosition = scene.cameras[cameraCounter].position;
        cameraUp = normalize(scene.cameras[cameraCounter].up);
        cameraGaze = normalize(scene.cameras[cameraCounter].gaze);
        cameraRight = normalize(crossProduct(cameraGaze,cameraUp));
        cameraDistance = scene.cameras[cameraCounter].near_distance;

        cameraReferencePointM.x = cameraPosition.x+cameraDistance*cameraGaze.x;
        cameraReferencePointM.y = cameraPosition.y+cameraDistance*cameraGaze.y;
        cameraReferencePointM.z = cameraPosition.z+cameraDistance*cameraGaze.z;

        topLeftPointQ.x = top*cameraUp.x + left*cameraRight.x + cameraReferencePointM.x;
        topLeftPointQ.y = top*cameraUp.y + left*cameraRight.y + cameraReferencePointM.y;
        topLeftPointQ.z = top*cameraUp.z + left*cameraRight.z + cameraReferencePointM.z;

        pixelWidth = (right-left)/width;
        pixelHeight = (top-bottom)/height;

        pixelCounter = 0;
		threadSharingHowMany = height/10;
		threadSharingLast = height % 10;
		std::thread thread0(startThreadFor,threadSharingHowMany,0,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread1(startThreadFor,threadSharingHowMany,threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread2(startThreadFor,threadSharingHowMany,2*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread3(startThreadFor,threadSharingHowMany,3*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread4(startThreadFor,threadSharingHowMany,4*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread5(startThreadFor,threadSharingHowMany,5*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread6(startThreadFor,threadSharingHowMany,6*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread7(startThreadFor,threadSharingHowMany,7*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread8(startThreadFor,threadSharingHowMany,8*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		std::thread thread9(startThreadFor,threadSharingHowMany,9*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
		if(threadSharingLast != 0){
			std::thread thread10(startThreadFor,threadSharingLast,10*threadSharingHowMany,width,imagePlane,topLeftPointQ,pixelWidth,pixelHeight,scene,cameraCounter);
			thread10.join();
		}
		//con_threads = std::thread::hardware_concurrency();
		//std::cout<<"Threaddd: " << con_threads << std::endl;
        /*for (int y = 0; y < height; ++y){
            for (int x = 0; x < width; ++x){
				/*if(y == 633){
					std::cout << "Gelemedik"<< std::endl;
				}
				if(y == 632){
					std::cout << "Geldik" << std::endl;
				}
				if(y == 634){
					std::cout << "Yattım allah kaldır beni" << std::endl;
				}
                currentPrimaryRay = generateRay(cameraPosition,topLeftPointQ,cameraUp,cameraRight,x,y,pixelWidth,pixelHeight);
				//std::cout << "Primary ray" << currentPrimaryRay.parameterConstant.x<<currentPrimaryRay.parameterConstant.y  << currentPrimaryRay.parameterCoefficient.x << currentPrimaryRay.parameterConstant.y << std::endl;
                tmpColor = getColorFromRay(currentPrimaryRay,scene,scene.cameras[cameraCounter].position,0);
				tmpColor.x = round(tmpColor.x);
				tmpColor.y = round(tmpColor.y);
				tmpColor.z = round(tmpColor.z);

				if(tmpColor.x>255){
					pixelColor[0] = 255;
				}
				else{
					araci = tmpColor.x;
					pixelColor[0] = araci;
				}
				if(tmpColor.y>255){
					pixelColor[1] = 255;
				}
				else{
					araci = tmpColor.y;
					pixelColor[1] = araci;
				}
				if(tmpColor.z>255){
					pixelColor[2] = 255;
				}
				else{
					araci = tmpColor.z;
					pixelColor[2] = araci;
				}
				imagePlane[pixelCounter++] = pixelColor[0];
	            imagePlane[pixelCounter++] = pixelColor[1];
	            imagePlane[pixelCounter++] = pixelColor[2];
            }
        }*/
		thread0.join();
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		thread5.join();
		thread6.join();
		thread7.join();
		thread8.join();
		thread9.join();
		write_ppm(imageOutputName, imagePlane, width, height);
		delete [] imagePlane;
    }
    // The code below creates a test pattern and writes
    // it to a PPM file to demonstrate the usage of the
    // ppm_write function.
    //
    // Normally, you would be running your ray tracing
    // code here to produce the desired image.
/*
    const RGB BAR_COLOR[8] =
    {
        { 255, 255, 255 },  // 100% White
        { 255, 255,   0 },  // Yellow
        {   0, 255, 255 },  // Cyan
        {   0, 255,   0 },  // Green
        { 255,   0, 255 },  // Magenta
        { 255,   0,   0 },  // Red
        {   0,   0, 255 },  // Blue
        {   0,   0,   0 },  // Black
    };

    int width = 640, height = 480;
    int columnWidth = width / 8;

    unsigned char* image = new unsigned char [width * height * 3];
    //Demek ki loopu bu sekilde yapiyorlar
    int i = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int colIdx = x / columnWidth;
            //Ayri ayri channel
            image[i++] = BAR_COLOR[colIdx][0];
            image[i++] = BAR_COLOR[colIdx][1];
            image[i++] = BAR_COLOR[colIdx][2];
        }
    }

    write_ppm("test.ppm", image, width, height);
*/
}

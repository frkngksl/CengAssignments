#include "scene.h"
#include <iostream>
#include <string>
#include "structObjects.h"
namespace fst
{

    void Scene::setTransformMatrix(Matrix4x4 &givenMatrix,math::Vector3f &uVec, math::Vector3f &vVec, math::Vector3f &wVec, math::Vector3f &center){
        double tempMatrix[16] = {
            uVec.x,uVec.y,uVec.z,-(uVec.x*center.x+uVec.y*center.y+uVec.z*center.z),
            vVec.x,vVec.y,vVec.z,-(vVec.x*center.x+vVec.y*center.y+vVec.z*center.z),
            wVec.x,wVec.y,wVec.z,-(wVec.x*center.x+wVec.y*center.y+wVec.z*center.z),
            0,0,0,1
        };

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                givenMatrix.matrix[i][j] = tempMatrix[i*4+j];
            }
        }
    }

    void Scene::doTransformSphere(const std::string &transformationString,math::Vector3f &center, double &radius,math::Vector3f &uVector,math::Vector3f &vVector, math::Vector3f &wVector){
        std::string tempString = transformationString;
        std::string transformCode;
        int indexForString;
        while((indexForString = tempString.find(" ")) != std::string::npos){
            transformCode = tempString.substr(0,indexForString);
            applyOpSphere(transformCode,center,radius,uVector,vVector,wVector);
            tempString.erase(0,indexForString+1);
        }
        if(!tempString.empty()){
            applyOpSphere(tempString,center,radius,uVector,vVector,wVector);
        }
    }


    void Scene::applyOpSphere(const std::string &transformCode,math::Vector3f &center, double &radius,math::Vector3f &uVector,math::Vector3f &vVector, math::Vector3f &wVector){
        Matrix4x4 *returningValue = NULL;
        std::string indexString = transformCode.substr(1);
        int index = std::stoi(indexString);
        if(transformCode[0] == 't'){
            center.x+= translations[index-1].x;
            center.y+= translations[index-1].y;
            center.z+= translations[index-1].z;
        }
        else if(transformCode[0] == 'r'){
            Matrix4x1 v0;
            Matrix4x1 uVec;
            Matrix4x1 vVec;
            Matrix4x1 wVec;
            Matrix4x1 *tmp;
            Matrix4x4 *returningValue = math::rotationMatrix(rotations[index-1].angle,rotations[index-1].x,rotations[index-1].y,rotations[index-1].z);

            v0.matrix[0][0] = center.x;
            v0.matrix[1][0] = center.y;
            v0.matrix[2][0] = center.z;
            v0.matrix[3][0] = 1;

            uVec.matrix[0][0] = uVector.x;
            uVec.matrix[1][0] = uVector.y;
            uVec.matrix[2][0] = uVector.z;
            uVec.matrix[3][0] = 0;

            vVec.matrix[0][0] = vVector.x;
            vVec.matrix[1][0] = vVector.y;
            vVec.matrix[2][0] = vVector.z;
            vVec.matrix[3][0] = 0;

            wVec.matrix[0][0] = wVector.x;
            wVec.matrix[1][0] = wVector.y;
            wVec.matrix[2][0] = wVector.z;
            wVec.matrix[3][0] = 0;

            tmp = math::matrixMultiplication4_1(returningValue,&v0);
            center.x = tmp->matrix[0][0];
            center.y = tmp->matrix[1][0];
            center.z = tmp->matrix[2][0];
            delete tmp;

            tmp = math::matrixMultiplication4_1(returningValue,&uVec);
            uVector.x = tmp->matrix[0][0];
            uVector.y = tmp->matrix[1][0];
            uVector.z = tmp->matrix[2][0];
            delete tmp;

            tmp = math::matrixMultiplication4_1(returningValue,&vVec);
            vVector.x = tmp->matrix[0][0];
            vVector.y = tmp->matrix[1][0];
            vVector.z = tmp->matrix[2][0];
            delete tmp;

            tmp = math::matrixMultiplication4_1(returningValue,&wVec);
            wVector.x = tmp->matrix[0][0];
            wVector.y = tmp->matrix[1][0];
            wVector.z = tmp->matrix[2][0];
            delete tmp;

        }
        else if(transformCode[0] == 's'){
            math::Vector3f newPoint;
            newPoint.x = center.x+radius;
            newPoint.y = center.y;
            newPoint.z = center.z;

            center.x *= scalings[index-1].x;
            center.y *= scalings[index-1].y;
            center.z *= scalings[index-1].z;

            newPoint.x *= scalings[index-1].x;
            newPoint.y *= scalings[index-1].y;
            newPoint.z *= scalings[index-1].z;

            radius = math::length(math::Vector3f(newPoint.x-center.x,newPoint.y-center.y,newPoint.z-center.z));
        }
    }
    void Scene::doTransformOperations(const std::string &transformationString,math::Vector3f &vertex0,math::Vector3f &vertex1, math::Vector3f &vertex2){
        std::string tempString;

        int indexForString;
        bool firstTime = true;
        std::string transformCode;
        tempString = transformationString;

        while ((indexForString = tempString.find(" ")) != std::string::npos) {
            transformCode = tempString.substr(0, indexForString);
            applyOp(transformCode,vertex0,vertex1,vertex2);
            tempString.erase(0, indexForString + 1);
        }
        if(!tempString.empty()){
            applyOp(tempString,vertex0,vertex1,vertex2);
        }
    }

    void Scene::applyOp(const std::string &transformCode, math::Vector3f &vertex0,math::Vector3f &vertex1, math::Vector3f &vertex2){
        Matrix4x4 *returningValue = NULL;
        std::string indexString = transformCode.substr(1);
        int index = std::stoi(indexString);

        if(transformCode[0] == 't'){
            //////std::cout <<"aloo: "<<  transformCode[0] << std::endl;
                ////std::cout << "-------------------translation-----------------------------" << std::endl;
            ////std::cout << "vertex 0 " << vertex0.x <<" "<< vertex0.y << " "<< vertex0.z << std::endl;
            ////std::cout << "vertex 1 " << vertex1.x <<" "<< vertex1.y <<" "<< vertex1.z << std::endl;
            ////std::cout << "vertex 2 " << vertex2.x <<" "<< vertex2.y <<" "<< vertex2.z << std::endl;
            vertex0.x+= translations[index-1].x;
            vertex0.y+= translations[index-1].y;
            vertex0.z+= translations[index-1].z;

            vertex1.x+= translations[index-1].x;
            vertex1.y+= translations[index-1].y;
            vertex1.z+= translations[index-1].z;

            vertex2.x+= translations[index-1].x;
            vertex2.y+= translations[index-1].y;
            vertex2.z+= translations[index-1].z;
            ////std::cout << "Rotation : " << translations[index-1].x<< " " << translations[index-1].y << " " << translations[index-1].z << std::endl;
            ////std::cout << "vertex 0 " << vertex0.x <<" "<< vertex0.y << " "<< vertex0.z << std::endl;
            ////std::cout << "vertex 1 " << vertex1.x <<" "<< vertex1.y <<" "<< vertex1.z << std::endl;
            ////std::cout << "vertex 2 " << vertex2.x <<" "<< vertex2.y <<" "<< vertex2.z << std::endl;
        }
        else if(transformCode[0] == 's'){
            //////std::cout <<"aloo: "<<  transformCode[0] << std::endl;
            ////std::cout << "-------------------scaling-----------------------------" << std::endl;
            ////std::cout << "vertex 0 " << vertex0.x <<" "<< vertex0.y << " "<< vertex0.z << std::endl;
            ////std::cout << "vertex 1 " << vertex1.x <<" "<< vertex1.y <<" "<< vertex1.z << std::endl;
            ////std::cout << "vertex 2 " << vertex2.x <<" "<< vertex2.y <<" "<< vertex2.z << std::endl;
            vertex0.x*= scalings[index-1].x;
            vertex0.y*= scalings[index-1].y;
            vertex0.z*= scalings[index-1].z;

            vertex1.x*= scalings[index-1].x;
            vertex1.y*= scalings[index-1].y;
            vertex1.z*= scalings[index-1].z;

            vertex2.x*= scalings[index-1].x;
            vertex2.y*= scalings[index-1].y;
            vertex2.z*= scalings[index-1].z;

            ////std::cout << "Scaling : " << scalings[index-1].x<< " " << scalings[index-1].y << " " << scalings[index-1].z << std::endl;
            ////std::cout << "vertex 0 " << vertex0.x <<" "<< vertex0.y << " "<< vertex0.z << std::endl;
            ////std::cout << "vertex 1 " << vertex1.x <<" "<< vertex1.y <<" "<< vertex1.z << std::endl;
            ////std::cout << "vertex 2 " << vertex2.x <<" "<< vertex2.y <<" "<< vertex2.z << std::endl;
        }
        else if(transformCode[0] == 'r' ){
            //////std::cout <<"aloo: "<<  transformCode[0] << std::endl;
            ////std::cout << "Rotation--------------------------" << std::endl;
            Matrix4x1 v0;
            Matrix4x1 v1;
            Matrix4x1 v2;
            Matrix4x1 *tmp;
            returningValue = math::rotationMatrix(rotations[index-1].angle,rotations[index-1].x,rotations[index-1].y,rotations[index-1].z);


            v0.matrix[0][0] = vertex0.x;
            v0.matrix[1][0] = vertex0.y;
            v0.matrix[2][0] = vertex0.z;
            v0.matrix[3][0] = 1;

            v1.matrix[0][0] = vertex1.x;
            v1.matrix[1][0] = vertex1.y;
            v1.matrix[2][0] = vertex1.z;
            v1.matrix[3][0] = 1;

            v2.matrix[0][0] = vertex2.x;
            v2.matrix[1][0] = vertex2.y;
            v2.matrix[2][0] = vertex2.z;
            v2.matrix[3][0] = 1;
            tmp = math::matrixMultiplication4_1(returningValue,&v0);
            vertex0.x = tmp->matrix[0][0];
            vertex0.y = tmp->matrix[1][0];
            vertex0.z = tmp->matrix[2][0];

            //std::cout << "Bir mi" << tmp->matrix[3][0] << std::endl;
            delete tmp;
            tmp = math::matrixMultiplication4_1(returningValue,&v1);
            vertex1.x = tmp->matrix[0][0];
            vertex1.y = tmp->matrix[1][0];
            vertex1.z = tmp->matrix[2][0];
            //std::cout << "Bir mi" << tmp->matrix[3][0] << std::endl;
            delete tmp;
            tmp = math::matrixMultiplication4_1(returningValue,&v2);
            vertex2.x = tmp->matrix[0][0];
            vertex2.y = tmp->matrix[1][0];
            vertex2.z = tmp->matrix[2][0];
            //std::cout << "Bir mi" << tmp->matrix[3][0] << std::endl;
            delete tmp;
            delete returningValue;
        }
    }

    void Scene::loadFromParser(const parser::Scene& parser)
    {   std::string tempString;
        int indexForString;
        std::string transformCode;
        Matrix4x4 *wholeTransform = NULL;
        Matrix4x4 *tempTransform;
        Matrix4x4 *tempForDelete;
        math::Vector3f vertex0;
        math::Vector3f vertex1;
        math::Vector3f vertex2;
        math::Vector3f uVector;
        math::Vector3f vVector;
        math::Vector3f wVector;
        double sphereRadius;
        Matrix4x1 *vertex0Matrix;
        Matrix4x1 *vertex1Matrix;
        Matrix4x1 *vertex2Matrix;
        Matrix4x4 transformMatrix;
        bool doTranslate = true;
        unsigned char *imageBuffer;
        int widthForTexture;
        int heightForTexture;

        for (auto& camera : parser.cameras)
        {
            cameras.push_back(Camera(
                math::Vector3f(camera.position.x, camera.position.y, camera.position.z),
                math::Vector3f(camera.gaze.x, camera.gaze.y, camera.gaze.z),
                math::Vector3f(camera.up.x, camera.up.y, camera.up.z),
                math::Vector4f(camera.near_plane.x, camera.near_plane.y, camera.near_plane.z, camera.near_plane.w),
                math::Vector2f(camera.image_width, camera.image_height),
                camera.image_name,
                camera.near_distance));
        }

        for (auto& pointlight : parser.point_lights)
        {
            point_lights.push_back(PointLight(
                math::Vector3f(pointlight.position.x, pointlight.position.y, pointlight.position.z),
                math::Vector3f(pointlight.intensity.x, pointlight.intensity.y, pointlight.intensity.z)));
        }

        for (auto& material : parser.materials)
        {
            materials.push_back(Material(
                math::Vector3f(material.ambient.x, material.ambient.y, material.ambient.z),
                math::Vector3f(material.diffuse.x, material.diffuse.y, material.diffuse.z),
                math::Vector3f(material.specular.x, material.specular.y, material.specular.z),
                math::Vector3f(material.mirror.x, material.mirror.y, material.mirror.z),
                material.phong_exponent));
        }

        for (auto &translation : parser.translations)
        {
            translations.push_back(
                Translation(translation.x, translation.y, translation.z));
        }

        for (auto &scaling : parser.scalings)
        {
            scalings.push_back(
                Scaling(scaling.x, scaling.y, scaling.z));
        }

        for (auto &rotation : parser.rotations)
        {
            rotations.push_back(
                Rotation(rotation.angle, rotation.x, rotation.y, rotation.z));
        }

        for (auto& vertex : parser.vertex_data)
        {
            vertex_data.push_back(math::Vector3f(vertex.x, vertex.y, vertex.z));
        }

        for (auto& tex_coord : parser.tex_coord_data)
        {
            tex_coord_data.push_back(math::Vector2f(tex_coord.x, tex_coord.y));
        }

        for (auto& texture : parser.textures)
        {
            /*std::string imageName;
            std::string interpolation;
            std::string decalMode;
            std::string appearance;*/
            read_jpeg_header(texture.imageName.c_str(), widthForTexture, heightForTexture);
            imageBuffer = new unsigned char[3*widthForTexture*heightForTexture];
            read_jpeg(texture.imageName.c_str(), imageBuffer, widthForTexture, heightForTexture);
            textures.push_back(Texture(widthForTexture, heightForTexture,imageBuffer,texture.imageName,texture.interpolation,texture.decalMode,texture.appearance));
        }

        for (auto& mesh : parser.meshes)
        {
            std::vector<Triangle> triangles;
            //wholeTransform = NULL;
            /*if(!mesh.transformations.empty()){
                wholeTransform = calculateTransformMatrix(mesh.transformations);
            }*/
            doTranslate = false;
            if(!mesh.transformations.empty()){
                doTranslate = true;
            }
            for (auto& face : mesh.faces)
            {
                vertex0 = vertex_data[face.v0_id - 1];
                vertex1 = vertex_data[face.v1_id - 1];
                vertex2 = vertex_data[face.v2_id - 1];
                /*////std::cout << "vertex 0 " << vertex0.x <<" "<< vertex0.y << " "<< vertex0.z << std::endl;
                ////std::cout << "vertex 1 " << vertex1.x <<" "<< vertex1.y <<" "<< vertex1.z << std::endl;
                ////std::cout << "vertex 2 " << vertex2.x <<" "<< vertex2.y <<" "<< vertex2.z << std::endl;*/
                if(doTranslate){
                    doTransformOperations(mesh.transformations,vertex0,vertex1,vertex2);
                }
                //////std::cout << "vertex 0 " << vertex0.x <<" "<< vertex0.y << " "<< vertex0.z << std::endl;
                //////std::cout << "vertex 1 " << vertex1.x <<" "<< vertex1.y <<" "<< vertex1.z << std::endl;
                //////std::cout << "vertex 2 " << vertex2.x <<" "<< vertex2.y <<" "<< vertex2.z << std::endl;
                triangles.push_back(Triangle(
                    vertex0,
                    vertex1 - vertex0,
                    vertex2 - vertex0,
                    face.v0_id -1,
                    face.v1_id -1,
                    face.v2_id -1,
                    mesh.texture_id));
            }
            /*for(int i=0;i<triangles.size();i++){
                ////std::cout  <<" Ucgen " <<  triangles[i].m_v0.x << " " << triangles[i].m_v0.y<< " " << triangles[i].m_v0.z << std::endl;
                ////std::cout  <<" Edge1 " <<  triangles[i].m_edge1.x << " " << triangles[i].m_edge1.y<< " " << triangles[i].m_edge1.z << std::endl;
                ////std::cout  <<" Edge2 " <<  triangles[i].m_edge2.x << " " << triangles[i].m_edge2.y<< " " << triangles[i].m_edge2.z << std::endl;
            }*/
            meshes.push_back(Mesh(std::move(triangles), mesh.material_id));
            delete wholeTransform;
        }

        for (auto& triangle : parser.triangles)
        {
            std::vector<Triangle> triangles;
            doTranslate = false;
            if(!triangle.transformations.empty()){
                doTranslate = true;
            }
            vertex0 = vertex_data[triangle.indices.v0_id - 1];
            vertex1 = vertex_data[triangle.indices.v1_id - 1];
            vertex2 = vertex_data[triangle.indices.v2_id - 1];
            if(doTranslate){
                ////std::cout << "Ucgen" << std::endl;
                doTransformOperations(triangle.transformations,vertex0,vertex1,vertex2);
            }
            triangles.push_back(Triangle(
                vertex0,
                vertex1 - vertex0,
                vertex2 - vertex0,
                triangle.indices.v0_id -1,
                triangle.indices.v1_id -1,
                triangle.indices.v2_id -1,
                triangle.texture_id));

            meshes.push_back(Mesh(std::move(triangles), triangle.material_id));
            delete wholeTransform;
        }

        for (auto& sphere : parser.spheres)
        {
            vertex0 = vertex_data[sphere.center_vertex_id-1];
            sphereRadius = sphere.radius;
            uVector = math::Vector3f(1,0,0);
            vVector = math::Vector3f(0,1,0);
            wVector = math::Vector3f(0,0,1);
            if(!sphere.transformations.empty()){

                doTransformSphere(sphere.transformations,vertex0,sphereRadius,uVector,vVector,wVector);
            }

            setTransformMatrix(transformMatrix,uVector,vVector,wVector,vertex0);
            ////std::cout << "Transform sphere: " << sphere.transformations << std::endl;
            spheres.push_back(Sphere(vertex0,
                sphereRadius, sphere.material_id,transformMatrix,sphere.texture_id));
        }

        background_color = math::Vector3f(parser.background_color.x, parser.background_color.y, parser.background_color.z);
        ambient_light = math::Vector3f(parser.ambient_light.x, parser.ambient_light.y, parser.ambient_light.z);
        shadow_ray_epsilon = parser.shadow_ray_epsilon;
        max_recursion_depth = parser.max_recursion_depth;
    }

    bool Scene::intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const
    {
        int index = 0;
        HitRecord temp;
        float min_distance = max_distance;
        for (auto& sphere : spheres)
        {
            if (sphere.intersect(ray, temp, min_distance))
            {
                min_distance = temp.distance;
                hit_record = temp;
                hit_record.isSphere = true;
                hit_record.indexOfItem = index;
            }
            index++;
        }
        index = 0;
        for (auto& mesh : meshes)
        {
            if (mesh.intersect(ray, temp, min_distance))
            {
                min_distance = temp.distance;
                hit_record = temp;
                hit_record.isSphere = false;
                hit_record.indexOfItem = index;
            }
            index++;
        }

        return min_distance != max_distance;
    }

    bool Scene::intersectShadowRay(const Ray& ray, float max_distance) const
    {
        for (auto& sphere : spheres)
        {
            if (sphere.intersectShadowRay(ray, max_distance))
            {
                return true;
            }
        }


        for (auto& mesh : meshes)
        {
            if (mesh.intersectShadowRay(ray, max_distance))
            {
		return true;
            }
        }

	return false;
    }
}

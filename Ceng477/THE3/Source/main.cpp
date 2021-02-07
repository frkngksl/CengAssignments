#include <iostream>
#include "parser.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//////-------- Global Variables -------/////////

GLuint gpuVertexBuffer;
GLuint gpuNormalBuffer;
GLuint gpuIndexBuffer;


double lastTime;
int numberOfFrames;

// Sample usage for reading an XML scene file
parser::Scene scene;
static GLFWwindow* win = NULL;

static void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}



double lengthOfVector(parser::Vec3f v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

parser::Vec3f normalize(parser::Vec3f v){
	parser::Vec3f returningValue = {0,0,0};
	double length;
	length=lengthOfVector(v);
    //Ask to assistant
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




parser::Vec3f crossProduct(parser::Vec3f a, parser::Vec3f b)
{
	parser::Vec3f returningValue = {0,0,0};

	returningValue.x = a.y*b.z-b.y*a.z;
	returningValue.y = b.x*a.z-a.x*b.z;
	returningValue.z = a.x*b.y-b.x*a.y;

	return returningValue;
}


void initNormals(){
	parser::Vec3f vertex0;
	parser::Vec3f vertex1;
	parser::Vec3f vertex2;
	parser::Vec3f temp1;
	parser::Vec3f temp2;
	parser::Vec3f normalTemp;
	size_t meshSize = scene.meshes.size();
	size_t triangleMeshSize;
	for(int i=0;i<meshSize;i++){
		triangleMeshSize = scene.meshes[i].faces.size();
		for(int j=0;j<triangleMeshSize;j++){
			vertex0 = scene.vertex_data[scene.meshes[i].faces[j].v0_id-1];
			vertex1 = scene.vertex_data[scene.meshes[i].faces[j].v1_id-1];
			vertex2 = scene.vertex_data[scene.meshes[i].faces[j].v2_id-1];

			temp1.x = vertex1.x-vertex0.x;
			temp1.y = vertex1.y-vertex0.y;
			temp1.z = vertex1.z-vertex0.z;

			temp2.x = vertex2.x-vertex0.x;
			temp2.y = vertex2.y-vertex0.y;
			temp2.z = vertex2.z-vertex0.z;

			normalTemp = crossProduct(temp1,temp2);
			//normalTemp = normalize(normalTemp);

			scene.meshes[i].normalVectors.push_back(normalTemp);
		}
	}
}

parser::Vec3f calculateAveragedNormals(int givenID){
    //Check incident or not
    parser::Vec3f returningValue;
    int incidentCount = 0;
    returningValue.x = 0;
    returningValue.y = 0;
    returningValue.z = 0;
    size_t meshSize = scene.meshes.size();
    int numberOfIncidents;
	size_t triangleMeshSize;
    for(int i=0;i<meshSize;i++){
        triangleMeshSize = scene.meshes[i].faces.size();
		for(int j=0;j<triangleMeshSize;j++){
            if(scene.meshes[i].faces[j].v0_id == givenID || scene.meshes[i].faces[j].v1_id == givenID || scene.meshes[i].faces[j].v2_id == givenID){
                returningValue.x += scene.meshes[i].normalVectors[j].x;
                returningValue.y += scene.meshes[i].normalVectors[j].y;
                returningValue.z += scene.meshes[i].normalVectors[j].z;
                incidentCount++;
            }
        }
    }
    returningValue.x = returningValue.x /incidentCount;
    returningValue.y = returningValue.y /incidentCount;
    returningValue.z = returningValue.z /incidentCount;
    //return normalize(returningValue);
    return returningValue;
}

void initLight(){
    glEnable(GL_LIGHTING);
    GLfloat lmodel_ambient[] = { scene.ambient_light.x,scene.ambient_light.y, scene.ambient_light.z, 1.0f };
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    for(int i=0;i<scene.point_lights.size();i++){
        GLfloat lightIntensity[] = {scene.point_lights[i].intensity.x,scene.point_lights[i].intensity.y,scene.point_lights[i].intensity.z,1.0f};
        GLfloat lightPosition[] = {scene.point_lights[i].position.x,scene.point_lights[i].position.y,scene.point_lights[i].position.z,1.0f};

        glLightfv(GL_LIGHT0+i,GL_POSITION,lightPosition);
        glLightfv(GL_LIGHT0+i,GL_DIFFUSE,lightIntensity);
        glLightfv(GL_LIGHT0+i,GL_SPECULAR,lightIntensity);
        glLightfv(GL_LIGHT0+i,GL_AMBIENT,lmodel_ambient);
        glEnable(GL_LIGHT0+i);
    }
}

void initCamera(){
    glViewport(0, 0, scene.camera.image_width, scene.camera.image_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(scene.camera.near_plane.x,scene.camera.near_plane.y,scene.camera.near_plane.z,scene.camera.near_plane.w,scene.camera.near_distance,scene.camera.far_distance);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(scene.camera.position.x,scene.camera.position.y,scene.camera.position.z,scene.camera.position.x+scene.camera.gaze.x,scene.camera.position.y+scene.camera.gaze.y,scene.camera.position.z+scene.camera.gaze.z,
        scene.camera.up.x,scene.camera.up.y,scene.camera.up.z);
}


void initScene(){
    GLfloat *verticeArray;
    GLfloat *normalArray;
    GLuint *indiceArray;
    parser::Vec3f tempNormalVec;
    int count=0;
    size_t vertexNum = scene.vertex_data.size();
    size_t numberOfTriangles = 0;
    size_t meshSize = scene.meshes.size();
	size_t triangleMeshSize;
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH); //Default bu
    glEnable(GL_NORMALIZE);
    if(scene.culling_enabled){
        //std::cout << "CULL ENABLED" << std::endl;
        glEnable(GL_CULL_FACE);
        if(scene.culling_face){
            //std::cout << "CULL FRONT" << std::endl;
            glCullFace(GL_FRONT);
        }
        else{
            //std::cout << "CULL BACK" << std::endl;
            glCullFace(GL_BACK);
        }
    }
    else{
        //std::cout << "CULL DISABLED" << std::endl;
        glDisable(GL_CULL_FACE);
        if(scene.culling_face){
            glCullFace(GL_FRONT);
            //std::cout << "CULL FRONT" << std::endl;
        }
        else{
            glCullFace(GL_BACK);
            //std::cout << "CULL BACK" << std::endl;
        }
    }

    for(int i=0;i<meshSize;i++){
        numberOfTriangles+=scene.meshes[i].faces.size();
    }
    glClearColor(scene.background_color.x, scene.background_color.y,scene.background_color.z, 1.0);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glGenBuffers(1, &gpuVertexBuffer);
    glGenBuffers(1, &gpuNormalBuffer);
    glGenBuffers(1, &gpuIndexBuffer);

    verticeArray = (GLfloat *)malloc(sizeof(float)*3*vertexNum);
    normalArray = (GLfloat *)malloc(sizeof(float)*3*vertexNum);
    indiceArray = (GLuint *)malloc(sizeof(int)*3*numberOfTriangles);

    for(int i=0;i<vertexNum;i++){
        //i is the id so check ids
        tempNormalVec = calculateAveragedNormals(i+1);
        normalArray[count] = tempNormalVec.x;
        verticeArray[count++] = scene.vertex_data[i].x;
        normalArray[count] = tempNormalVec.y;
        verticeArray[count++] = scene.vertex_data[i].y;
        normalArray[count] = tempNormalVec.z;
        verticeArray[count++] = scene.vertex_data[i].z;

    }

    count = 0;
    for(int i=0;i<meshSize;i++){
        triangleMeshSize = scene.meshes[i].faces.size();
        for(int j=0;j<triangleMeshSize;j++){
            indiceArray[count++] = scene.meshes[i].faces[j].v0_id-1;
            indiceArray[count++] = scene.meshes[i].faces[j].v1_id-1;
            indiceArray[count++] = scene.meshes[i].faces[j].v2_id-1;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER,gpuVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*vertexNum,verticeArray,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,gpuNormalBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*vertexNum,normalArray,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,gpuIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*3*numberOfTriangles,indiceArray,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    free(verticeArray);
    free(normalArray);
    free(indiceArray);

    initLight();
    initCamera();
}



void renderScene(){
    size_t meshSize = scene.meshes.size();
    std::string tempString;
    parser::Vec3f tempTranslation;
    parser::Vec3f tempScaling;
    parser::Vec4f tempRotation;
    glBindBuffer(GL_ARRAY_BUFFER,gpuVertexBuffer);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER, gpuNormalBuffer);
    glNormalPointer(GL_FLOAT,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,gpuIndexBuffer);
    int offsetForVertex=0;
    glClearColor(scene.background_color.x, scene.background_color.y,scene.background_color.z, 1.0);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    for(int i=0;i<meshSize;i++){
        glPushMatrix();
        for(int j=scene.meshes[i].transformations.size()-1;j>=0;j--){
            tempString = scene.meshes[i].transformations[j].transformation_type;
            if(!(tempString.compare("Translation"))){
                tempTranslation = scene.translations[scene.meshes[i].transformations[j].id-1];
                glTranslatef(tempTranslation.x,tempTranslation.y,tempTranslation.z);
            }
            else if(!(tempString.compare("Rotation"))){
                tempRotation = scene.rotations[scene.meshes[i].transformations[j].id-1];
                glRotatef(tempRotation.x,tempRotation.y,tempRotation.z,tempRotation.w);
            }
            else if(!(tempString.compare("Scaling"))){
                tempScaling = scene.scalings[scene.meshes[i].transformations[j].id-1];
                glScalef(tempScaling.x,tempScaling.y,tempScaling.z);
            }
        }
        if(!(scene.meshes[i].mesh_type.compare("Solid"))){
            //std::cout << "Soliddd" << std::endl;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else if(!(scene.meshes[i].mesh_type.compare("Wireframe"))){
            //std::cout << "Wireframe" << std::endl;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        parser::Material tempMaterial = scene.materials[scene.meshes[i].material_id-1];
        GLfloat ambColor[4] = {tempMaterial.ambient.x,tempMaterial.ambient.y,tempMaterial.ambient.z,1.0};
        GLfloat diffColor[4] = {tempMaterial.diffuse.x,tempMaterial.diffuse.y,tempMaterial.diffuse.z,1.0};
        GLfloat specColor[4] = {tempMaterial.specular.x,tempMaterial.specular.y,tempMaterial.specular.z,1.0};
        GLfloat specExp[1] = {tempMaterial.phong_exponent};
        glMaterialfv(GL_FRONT,GL_AMBIENT,ambColor);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,diffColor);
        glMaterialfv(GL_FRONT,GL_SPECULAR,specColor);
        glMaterialfv(GL_FRONT,GL_SHININESS,specExp);
        glDrawElements(GL_TRIANGLES, scene.meshes[i].faces.size()*3, GL_UNSIGNED_INT,reinterpret_cast<void*>(offsetForVertex*3*sizeof(GLuint)));
        offsetForVertex+=scene.meshes[i].faces.size();
        glPopMatrix();
    }
    // bind with 0, so, switch back to normal pointer operation
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void showFPS(GLFWwindow *pWindow)
{
    // Measure speed
     double currentTime = glfwGetTime();
     double delta = currentTime - lastTime;
	 char ss[500] = {};
     numberOfFrames++;
     if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago

         double fps = ((double)(numberOfFrames)) / delta;
         //Oran orantı

         sprintf(ss,"CENG477 - HW3 [%.2lf FPS]",fps);

         glfwSetWindowTitle(pWindow, ss);

         numberOfFrames = 0;
         lastTime = currentTime;
     }
}


int main(int argc, char* argv[]) {
    scene.loadFromXml(argv[1]);
    int imageWidth;
    int imageHeight;
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    //Create window
    win = glfwCreateWindow(scene.camera.image_width, scene.camera.image_height, "CENG477 - HW3", NULL, NULL);
    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(win);
    //Same

    //Init glew
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    //Set key callbacks
    glfwSetKeyCallback(win, keyCallback);

    //?
    glfwSwapInterval(1);

    initNormals();
    initScene();
    while(!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glfwGetFramebufferSize(win, &imageWidth, &imageHeight);
        glViewport(0, 0, imageWidth, imageHeight);
        renderScene();
        showFPS(win);
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();

    exit(EXIT_SUCCESS);

    return 0;
}

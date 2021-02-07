#include "helper.h"

static GLFWwindow* win = NULL;
static GLFWmonitor* monitor = NULL;
int widthWindow = 1000, heightWindow = 1000;

float angleConstant = 0.05*(3.141592f/180.0f);
// Shaders
GLuint idProgramShader;
GLuint idFragmentShader;
GLuint idVertexShader;
GLuint idJpegTexture;
GLuint idHeightTexture;



GLuint idMVPMatrix;
GLuint idMVMatrix;
GLuint idHeightFactor;
GLuint textureID;
GLuint heightID;
GLuint widthTextureShader;
GLuint heightTextureShader;
GLuint cameraPositionShader;
GLuint lightPositionShader;
GLuint textureShiftID;

// Buffers
GLuint idVertexBuffer;
GLuint idIndexBuffer;

int textureWidth, textureHeight;
float heightFactor = 10.0f;
int shiftAmount = 0;

Camera camera;
Camera initialCamera;

glm::vec3 lightPos;
glm::mat4 projectionMatrix;
glm::mat4 viewingMatrix;
glm::mat4 modelingMatrix = glm::mat4(1.0f);
glm::mat4 mvp;
glm::mat4 mv;

GLuint depthMapFBO;
GLuint depthCubemap;
bool lightPosFlag = false;
unsigned int VAO;



bool increaseHeightFactor = false;
bool decreaseHeightFactor = false;

bool increaseLightY = false;
bool decreaseLightY = false;
bool increaseLightX = false;
bool decreaseLightX = false;
bool increaseLightZ = false;
bool decreaseLightZ = false;

bool texturePlaneLeft = false;
bool texturePlaneRight = false;

bool returnToInitial = false;

bool setFullScreen = false;
bool isFullScreen = false;

bool increaseSpeed = false;
bool decreaseSpeed = false;

bool stopThePlane = false;

bool increaseAngleForUp = false;
bool decreaseAngleForUp = false;

bool increaseAngleForLeft = false;
bool decreaseAngleForLeft = false;


int oldSizex = 0;
int oldSizey = 0;

int oldPosx = 0;
int oldPosy = 0;

float camSpeed = 0;




void initScene(){
    GLfloat *verticeArray;
    GLuint *indiceArray;
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glClearColor(0,0,0,1.0);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glGenBuffers(1, &idVertexBuffer);
    //Gen buffer
    glGenBuffers(1, &idIndexBuffer);

    //corner cases
    verticeArray = (GLfloat *)malloc(sizeof(float)*3*(textureWidth+1)*(textureHeight+1));
    indiceArray = (GLuint *)malloc(sizeof(int)*3*2*textureWidth*textureHeight);

    int counter = 0;
    //textureHeight = 1;
    // textureWidth = 5;

    for(int i=0;i<=textureHeight;i++){
        for(int j=0;j<=textureWidth;j++){
            verticeArray[counter++] = j;
            verticeArray[counter++] = 0;
            verticeArray[counter++] = i;
            //std::cout << "vertex" << j <<" " << i << std::endl;
        }
    }
//0,width+0,width+1 - 1,width+0,width+1 --- 1,width+1,width+2 - 2,width +1 width+2
    counter = 0;
    int x = (textureHeight+1)*(textureWidth+1);
    int modAl = textureWidth+1;
    int solUst = textureWidth+2;
    int sagAlt = textureWidth+1;
    int asagi = 1;
    for(int i=textureWidth+2;i<x;i++){
        if((i) % (modAl) == 0){

            //std::cout << "Oldu: " << x << std::endl;
            continue;
        }
        indiceArray[counter++] = i-solUst;
        indiceArray[counter++] = i-asagi;
        indiceArray[counter++] = i-sagAlt;
        //std::cout << "İlk üçgen: " << x << textureWidth+x+1 << x+1 << std::endl;
        indiceArray[counter++] = i-sagAlt;
        indiceArray[counter++] = i-1;
        indiceArray[counter++] = i;
        //std::cout << "İkinci üçgen: " << x+1 << textureWidth+x+1 << textureWidth+x+2 << "X: " << x+1%textureWidth<< std::endl;

    }


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, idVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*(textureWidth+1)*(textureHeight+1),verticeArray,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,idIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*3*2*textureWidth*textureHeight,indiceArray,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glBindBuffer(GL_ARRAY_BUFFER,idVertexBuffer);
    //Bind buffer
    //glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*(textureWidth+1)*(textureHeight+1),verticeArray,GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glBufferData is a function specifically targeted to copy user-defined data into the currently bound buffer
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,idIndexBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*3*2*textureWidth*textureHeight,indiceArray,GL_STATIC_DRAW);
    //glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER,0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    free(verticeArray);
    free(indiceArray);

    //float fovyRad = (float) (45.0 / 180.0) * M_PI;
    //float fovyRad = glm::radians(45.0f);
    projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);

    //initialCamera.gaze = glm::vec3(0,-0.34,0.94);
    //initialCamera.up = glm::vec3(-0.017,0.94,0.34);
    initialCamera.gaze = glm::vec3(0.0f,0.0f,1.0f);
    initialCamera.up = glm::vec3(0.0f,1.0f,0.0f);
    initialCamera.u = glm::vec3(-1.0f,0.0f,0.0f); //vxw
    initialCamera.position = glm::vec3(textureWidth/2.0, textureWidth/10.0, -textureWidth/4.0);
    //initialCamera.position  = glm::vec3(495, 380, -631);
    glm::vec3 center = initialCamera.position  + initialCamera.gaze;

    camera.gaze = glm::vec3(0.0f,0.0f,1.0f);
    camera.up = glm::vec3(0.0f,1.0f,0.0f);
    camera.u = glm::vec3(-1.0f,0.0f,0.0f);
    camera.position = glm::vec3(textureWidth/2.0,textureWidth/10.0,-textureWidth/4.0);
    //center = center/glm::length(center);
    viewingMatrix = glm::lookAt(initialCamera.position, center, initialCamera.up);
    lightPos = glm::vec3(textureWidth/2.0,100,textureHeight/2.0);
    idMVPMatrix = glGetUniformLocation(idProgramShader, "MVP");
    idMVMatrix = glGetUniformLocation(idProgramShader, "MV");
    idHeightFactor = glGetUniformLocation(idProgramShader, "heightFactor");
    textureID = glGetUniformLocation(idProgramShader,"rgbTexture");
    heightID = glGetUniformLocation(idProgramShader,"yMapTexture");
    heightTextureShader = glGetUniformLocation(idProgramShader,"heightTexture");
    widthTextureShader = glGetUniformLocation(idProgramShader,"widthTexture");
    cameraPositionShader = glGetUniformLocation(idProgramShader,"cameraPosition");
    lightPositionShader = glGetUniformLocation(idProgramShader,"lightPosition");
    textureShiftID = glGetUniformLocation(idProgramShader,"textureShift");

    mvp = projectionMatrix*viewingMatrix*modelingMatrix;
    //?
    /*
    std::cout << "MVP: " << mvp[0][0] << "  " << mvp[0][1] << " "  << mvp[0][2] <<" "<< mvp[0][3] << std::endl;
    std::cout << "MVP: " << mvp[1][0] << " " << mvp[1][1] << " " << mvp[1][2] <<" "<< mvp[1][3] << std::endl;
    std::cout << "MVP: " << mvp[2][0] << " " << mvp[2][1] << " " << mvp[2][2] <<" "<< mvp[2][3] << std::endl;
    std::cout << "MVP: " << mvp[3][0] << " " << mvp[3][1] << " " << mvp[3][2] <<" "<< mvp[3][3] << std::endl;
    */
    mv = viewingMatrix*modelingMatrix;
    glUniformMatrix4fv(idMVPMatrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(idMVMatrix,1,GL_FALSE, &mv[0][0]);
    glUniform1i(textureID,0);
    glUniform1i(heightID,1);
    glUniform1i(heightTextureShader,textureHeight);
    glUniform1i(widthTextureShader,textureWidth);
    glUniform1f(idHeightFactor,heightFactor);
    glUniform3fv(lightPositionShader,1,&lightPos.x);
    glUniform3fv(cameraPositionShader,1,&initialCamera.position.x);
    glUniform1i(textureShiftID,shiftAmount);
}


void renderScene(){
    glClearColor(0,0,0, 1.0);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if(increaseHeightFactor){
        heightFactor+=0.5;
        //increaseHeightFactor = false;
        glUniform1f(idHeightFactor,heightFactor);
    }
    if(decreaseHeightFactor){
        heightFactor-=0.5;
        //decreaseHeightFactor = false;
        glUniform1f(idHeightFactor,heightFactor);
    }
    if(increaseLightY){
        lightPos.y+=5;
        //increaseLightY = false;
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }
    if(decreaseLightY){
        lightPos.y-=5;
        //decreaseLightY = false;
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }
    if(increaseLightX){
        lightPos.x+=5;
        //increaseLightX = false;
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }
    if(decreaseLightX){
        lightPos.x-=5;
        //decreaseLightX = false;
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }
    if(increaseLightZ){
        lightPos.z+=5;
        //increaseLightZ = false;
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }
    if(decreaseLightZ){
        lightPos.z-=5;
        //decreaseLightZ = false;
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }
    if(texturePlaneLeft){
        shiftAmount-=1;
        //texturePlaneLeft = false;
        glUniform1i(textureShiftID,shiftAmount);
    }
    if(texturePlaneRight){
        shiftAmount+=1;
        //texturePlaneRight = false;
        glUniform1i(textureShiftID,shiftAmount);
    }
    if(setFullScreen){
        setFullScreen = false;
        // backup window position and window size

        // get resolution of monitor
        if(!isFullScreen){
            isFullScreen = true;
            glfwGetWindowPos( win, &oldPosx, &oldPosy );
            glfwGetWindowSize( win, &oldSizex, &oldSizey );

            const GLFWvidmode * mode = glfwGetVideoMode(monitor);

            // switch to full screen
            glfwSetWindowMonitor( win, monitor, 0, 0, mode->width, mode->height, 0 );

        }
        else{
             glfwSetWindowMonitor( win, nullptr,  oldPosx, oldPosy, oldSizex, oldSizey, 0 );
             isFullScreen = false;
        }

    }
    if(increaseSpeed){
        //increaseSpeed = false;
        camSpeed+=0.01;
        if(camSpeed < 0.000001 && -0.000001 < camSpeed){
            camSpeed = 0;
        }
    }
    if(decreaseSpeed){
        //decreaseSpeed = false;
        camSpeed-=0.01;
        if(camSpeed < 0.000001 && -0.000001 < camSpeed){
            camSpeed = 0;
        }
    }
    if(stopThePlane){
        //stopThePlane = false;
        camSpeed = 0;
    }
    if(increaseAngleForLeft){
        //increaseAngleForLeft = false;
        glm::mat4 tempRotate = glm::rotate(glm::mat4(1.0f),0.05f ,camera.u);
        camera.gaze = glm::vec3(tempRotate*glm::vec4(camera.gaze,0.0f));
        camera.gaze = glm::normalize(camera.gaze);
        camera.up = glm::vec3(tempRotate*glm::vec4(camera.up,0.0f));
        camera.up = glm::normalize(camera.up);
        camera.u = glm::cross(camera.up,-camera.gaze);
        camera.u = glm::normalize(camera.u);

    }
    if(decreaseAngleForLeft){
        //decreaseAngleForLeft = false;
        glm::mat4 tempRotate = glm::rotate(glm::mat4(1.0f),-0.05f ,camera.u);
        camera.gaze = glm::vec3(tempRotate*glm::vec4(camera.gaze,0.0f));
        camera.gaze = glm::normalize(camera.gaze);
        camera.up = glm::vec3(tempRotate*glm::vec4(camera.up,0.0f));
        camera.up = glm::normalize(camera.up);
        camera.u = glm::cross(camera.up,-camera.gaze);
        camera.u = glm::normalize(camera.u);
    }
    if(increaseAngleForUp){
        //increaseAngleForUp = false;
        glm::mat4 tempRotate = glm::rotate(glm::mat4(1.0f),0.05f ,camera.up);
        camera.gaze = glm::vec3(tempRotate*glm::vec4(camera.gaze,0.0f));
        camera.gaze = glm::normalize(camera.gaze);
        camera.u = glm::vec3(tempRotate*glm::vec4(camera.u,0.0f));
        camera.u = glm::normalize(camera.u);
        camera.up = glm::cross(-camera.u,-camera.gaze);
        camera.up = glm::normalize(camera.up);
    }
    if(decreaseAngleForUp){
        //decreaseAngleForUp = false;
        glm::mat4 tempRotate = glm::rotate(glm::mat4(1.0f), -0.05f ,camera.up);
        camera.gaze = glm::vec3(tempRotate*glm::vec4(camera.gaze,0.0f));
        camera.gaze = glm::normalize(camera.gaze);
        camera.u = glm::vec3(tempRotate*glm::vec4(camera.u,0.0f));
        camera.u = glm::normalize(camera.u);
        camera.up = glm::cross(-camera.u,-camera.gaze);
        camera.up = glm::normalize(camera.up);
    }
    if(returnToInitial){
        //returnToInitial = false;
        camera.gaze = initialCamera.gaze;
        camera.up = initialCamera.up;
        camera.u = initialCamera.u;
        camera.position = initialCamera.position;
        camSpeed = 0;
        shiftAmount = 0;
        lightPos = glm::vec3(textureWidth/2.0,100,textureHeight/2.0);
        //texturePlaneLeft = false;
        heightFactor = 10.0f;
        glUniform1f(idHeightFactor,heightFactor);
        glUniform1i(textureShiftID,shiftAmount);
        glUniform3fv(lightPositionShader,1,&lightPos.x);
    }


    camera.position += camera.gaze*camSpeed;
    //center = center/glm::length(center);
    glm::vec3 center = camera.position  + camera.gaze;
    viewingMatrix = glm::lookAt(camera.position, center, camera.up);
    mvp = projectionMatrix*viewingMatrix*modelingMatrix;
    mv = viewingMatrix*modelingMatrix;
    glUniformMatrix4fv(idMVPMatrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(idMVMatrix,1,GL_FALSE, &mv[0][0]);
    glUniform3fv(cameraPositionShader,1,&initialCamera.position.x);

    glfwGetFramebufferSize(win, &widthWindow, &heightWindow);
    glViewport(0, 0, widthWindow, heightWindow);


    glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 2*textureWidth*textureHeight * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//glUniform3fv(eyePosLoc[activeProgramIndex], 1, glm::value_ptr(eyePos));
    //glDrawElements(GL_TRIANGLES,2*textureWidth*textureHeight*3, GL_UNSIGNED_INT,0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


static void errorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else{
        //if(action == GLFW_REPEAT || action == GLFW_PRESS){
            if(key == GLFW_KEY_R && action == GLFW_PRESS){
                increaseHeightFactor = true;
            }
            else if(key == GLFW_KEY_R && action == GLFW_RELEASE){
                increaseHeightFactor = false;
            }
            else if(key == GLFW_KEY_F && action == GLFW_PRESS){
                decreaseHeightFactor = true;
            }
            else if(key == GLFW_KEY_F && action == GLFW_RELEASE){
                decreaseHeightFactor = false;
            }
            else if(key == GLFW_KEY_T && action == GLFW_PRESS){
                increaseLightY = true;
            }
            else if(key == GLFW_KEY_T && action == GLFW_RELEASE){
                increaseLightY = false;
            }
            else if(key == GLFW_KEY_G  && action == GLFW_PRESS){
                decreaseLightY = true;
            }
            else if(key == GLFW_KEY_G  && action == GLFW_RELEASE){
                decreaseLightY = false;
            }
            else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
                increaseLightZ = true;
            }
            else if(key == GLFW_KEY_UP && action == GLFW_RELEASE){
                increaseLightZ = false;
            }
            else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
                decreaseLightZ = true;
            }
            else if(key == GLFW_KEY_DOWN && action == GLFW_RELEASE){
                decreaseLightZ = false;
            }
            else if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
                increaseLightX = true;
            }
            else if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
                increaseLightX = false;
            }
            else if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
                decreaseLightX = true;
            }
            else if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
                decreaseLightX = false;
            }
            else if(key == GLFW_KEY_Q && action == GLFW_PRESS){
                //std::cout << "Oldu ? " << std::endl;
                texturePlaneLeft = true;
            }
            else if(key == GLFW_KEY_Q && action == GLFW_RELEASE){
                //std::cout << "Oldu ? " << std::endl;
                texturePlaneLeft = false;
            }
            else if(key == GLFW_KEY_E && action == GLFW_PRESS){
                texturePlaneRight = true;
            }
            else if(key == GLFW_KEY_E && action == GLFW_RELEASE){
                texturePlaneRight = false;
            }
            else if (key == GLFW_KEY_I && action == GLFW_PRESS){
                //TODO Not Completed Yet TODO
                returnToInitial = true;
            }
            else if (key == GLFW_KEY_I && action == GLFW_RELEASE){
                //TODO Not Completed Yet TODO
                returnToInitial = false;
            }
            else if (key == GLFW_KEY_P && (action == GLFW_PRESS || action == GLFW_REPEAT)){
                setFullScreen = true;
                //Shouldn't be release concept
            }
            else if(key == GLFW_KEY_Y && action == GLFW_PRESS){
                increaseSpeed = true;
            }
            else if(key == GLFW_KEY_Y && action == GLFW_RELEASE){
                increaseSpeed = false;
            }
            else if(key == GLFW_KEY_H && action == GLFW_PRESS){
                decreaseSpeed = true;
            }
            else if(key == GLFW_KEY_H && action == GLFW_RELEASE){
                decreaseSpeed = false;
            }
            else if(key == GLFW_KEY_X  && action == GLFW_PRESS){
                stopThePlane = true;
            }
            else if(key == GLFW_KEY_X  && action == GLFW_RELEASE){
                stopThePlane = false;
            }
            else if(key == GLFW_KEY_A && action == GLFW_PRESS){
                increaseAngleForUp = true;
            }
            else if(key == GLFW_KEY_A && action == GLFW_RELEASE){
                increaseAngleForUp = false;
            }
            else if(key == GLFW_KEY_D && action == GLFW_PRESS){
                decreaseAngleForUp = true;
            }
            else if(key == GLFW_KEY_D && action == GLFW_RELEASE){
                decreaseAngleForUp = false;
            }
            else if(key == GLFW_KEY_W && action == GLFW_PRESS){
                increaseAngleForLeft = true;
            }
            else if(key == GLFW_KEY_W && action == GLFW_RELEASE){
                increaseAngleForLeft = false;
            }
            else if(key == GLFW_KEY_S && action == GLFW_PRESS){
                decreaseAngleForLeft = true;
            }
            else if(key == GLFW_KEY_S && action == GLFW_RELEASE){
                decreaseAngleForLeft = false;
            }
        //}
    }
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    printf("Please provide height and texture image files!\n");
    exit(-1);
  }

  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); // This is required for remote
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); // This might be used for local

  win = glfwCreateWindow(widthWindow, heightWindow, "CENG477 - HW4", NULL, NULL);

  if (!win) {
      glfwTerminate();
      exit(-1);
  }
  glfwMakeContextCurrent(win);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

      glfwTerminate();
      exit(-1);
  }
  monitor = glfwGetPrimaryMonitor();
  std::string shaderVertName("shader.vert");
  std::string shaderFragName("shader.frag");
  initShaders(idProgramShader,shaderVertName,shaderFragName);
  glUseProgram(idProgramShader);

  //CallBack program
  glfwSetKeyCallback(win, keyCallback);

  initTexture(argv[1], argv[2], &textureWidth, &textureHeight);


  initScene();
  while(!glfwWindowShouldClose(win)) {
    glfwPollEvents();

    renderScene();

    glfwSwapBuffers(win);

  }


  glfwDestroyWindow(win);
  glfwTerminate();
  return 0;
}

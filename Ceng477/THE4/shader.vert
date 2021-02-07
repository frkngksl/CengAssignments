#version 330
//Next we declare all the input vertex attributes in the vertex shader with the in keyword. Right now we only care about position data so we only need a single vertex attribute.

layout(location = 0) in vec3 position;

// Data from CPU
uniform mat4 MVP; // ModelViewProjection Matrix
uniform mat4 MV; // ModelView idMVPMatrix
uniform vec3 cameraPosition;
uniform float heightFactor;
uniform vec3 lightPosition;

// Texture-related data
uniform sampler2D rgbTexture;
uniform sampler2D yMapTexture;
uniform int widthTexture;
uniform int heightTexture;
uniform int textureShift;

// Output to Fragment Shader
out vec2 textureCoordinate; // For texture-color
out vec3 vertexNormal; // For Lighting computation
out vec3 ToLightVector; // Vector from Vertex to Light;
out vec3 ToCameraVector; // Vector from Vertex to Camera;

float realTextureShift = textureShift*1.0/widthTexture;

float getHeightValue(float posX, float posZ){
     float returnValue = texture(yMapTexture,vec2(1 -posX/widthTexture+realTextureShift,1-posZ/heightTexture)).x;
     return returnValue*heightFactor;
}


// Flip the image upside down such that the first element in
// image1D corresponds to the bottom-left corner of the image.
// This is what OpenGL expects (texcoord [0, 0] means the
// bottom-left corner).



vec3 neighborFromHell(vec3 ourVertex){
    vec3 leftVertex = vec3(ourVertex.x-1,getHeightValue(ourVertex.x-1,ourVertex.z),ourVertex.z);
    vec3 rightVertex = vec3(ourVertex.x+1,getHeightValue(ourVertex.x+1,ourVertex.z),ourVertex.z);
    vec3 bottomVertex = vec3(ourVertex.x,getHeightValue(ourVertex.x,ourVertex.z+1),ourVertex.z+1);
    vec3 topVertex = vec3(ourVertex.x,getHeightValue(ourVertex.x,ourVertex.z-1),ourVertex.z-1);
    //because of the slice this is not our neighbor
    //vec3 topLeftVertex = vec3(ourVertex.x-1,getHeightValue(ourVertex-1,ourVertex.z+1),ourVertex.z+1);
    vec3 topRightVertex = vec3(ourVertex.x+1,getHeightValue(ourVertex.x+1,ourVertex.z-1),ourVertex.z-1);
    vec3 bottomLeftVertex = vec3(ourVertex.x-1,getHeightValue(ourVertex.x-1,ourVertex.z+1),ourVertex.z+1);
    //because of the slice this is not our neighbor
    //vec3 bottomRightVertex = vec3(ourVertex.x+1,getHeightValue(ourVertex+1,ourVertex.z-1),ourVertex.z-1);

    vec3 normal1 = cross(leftVertex-topVertex,ourVertex-topVertex);
    vec3 normal2 = cross(topVertex-topRightVertex,ourVertex-topRightVertex);
    vec3 normal3 = cross(topRightVertex-rightVertex,ourVertex-rightVertex);
    vec3 normal4 = cross(rightVertex-bottomVertex,ourVertex-bottomVertex);
    vec3 normal5 = cross(bottomVertex-bottomLeftVertex,ourVertex-bottomLeftVertex);
    vec3 normal6 = cross(bottomLeftVertex-leftVertex,ourVertex-leftVertex);
    //Edge points ?
    vec3 totalNormal = vec3(0,0,0);
    totalNormal+=normal1;
    totalNormal+=normal2;
    totalNormal+=normal3;
    totalNormal+=normal4;
    totalNormal+=normal5;
    totalNormal+=normal6;
    totalNormal = totalNormal/6;
    totalNormal = normalize(totalNormal);

    return totalNormal;

}

void main(){
    // get texture value, compute height

    // compute normal vector using also the heights of neighbor vertices

    // compute toLight vector vertex coordinate in VCS

    //M zaten bir olum

   // set gl_Position variable correctly to give the transformed vertex position
   textureCoordinate = vec2(1 -position.x/widthTexture+realTextureShift,1-position.z/heightTexture);
   float yValue = getHeightValue(position.x,position.z);
   vec3 newPosition = vec3(position.x,yValue,position.z);
   vertexNormal = neighborFromHell(newPosition);
   ToLightVector = normalize(lightPosition-newPosition);
   ToCameraVector = normalize(cameraPosition-newPosition);
   gl_Position = MVP*vec4(newPosition,1.0);
}

#pragma once

#include "utility.h"
#include <cmath>
#include <iostream>
#include "structObjects.h"
#define PI 3.14159265
namespace fst
{
    namespace math
    {
        struct Vector3f
        {
            float x, y, z;

            Vector3f() = default;
            explicit Vector3f(float a)
                : x(a)
                , y(a)
                , z(a)
            {}
            Vector3f(float a, float b, float c)
                : x(a)
                , y(b)
                , z(c)
            {}

            Vector3f operator - () const
            {
                return Vector3f(-x, -y, -z);
            }

            Vector3f operator + (const Vector3f& vec) const
            {
                return Vector3f(x + vec.x, y + vec.y, z + vec.z);
            }

            Vector3f operator - (const Vector3f& vec) const
            {
                return Vector3f(x - vec.x, y - vec.y, z - vec.z);
            }

            Vector3f operator * (const Vector3f& vec) const
            {
                return Vector3f(x * vec.x, y * vec.y, z * vec.z);
            }

            Vector3f operator / (const Vector3f& vec) const
            {
                return Vector3f(x / vec.x, y / vec.y, z / vec.z);
            }

            float operator [] (int i) const
            {
                return (&x)[i];
            }
        };

        static Vector3f operator * (const Vector3f& vec, float scalar)
        {
            return Vector3f(vec.x * scalar, vec.y * scalar, vec.z * scalar);
        }

        static Vector3f operator * (float scalar, const Vector3f& vec)
        {
            return Vector3f(vec.x * scalar, vec.y * scalar, vec.z * scalar);
        }

        static Vector3f operator / (const Vector3f& vec, float scalar)
        {
            return Vector3f(vec.x / scalar, vec.y / scalar, vec.z / scalar);
        }

        static Vector3f operator / (float scalar, const Vector3f& vec)
        {
            return Vector3f(scalar / vec.x, scalar / vec.y, scalar / vec.z);
        }

        static float length(const Vector3f& vec)
        {
            return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
        }

        static float dot(const Vector3f& vec1, const Vector3f& vec2)
        {
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        }

        static Vector3f cross(const Vector3f& vec1, const Vector3f& vec2)
        {
            return Vector3f(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
        }

        static Vector3f normalize(const Vector3f& vec)
        {
            return vec / length(vec);
        }

        static Vector3f min(const Vector3f& vec1, const Vector3f& vec2)
        {
            return Vector3f(math::min(vec1.x, vec2.x), math::min(vec1.y, vec2.y), math::min(vec1.z, vec2.z));
        }

        static Vector3f max(const Vector3f& vec1, const Vector3f& vec2)
        {
            return Vector3f(math::max(vec1.x, vec2.x), math::max(vec1.y, vec2.y), math::max(vec1.z, vec2.z));
        }

        static Vector3f clamp(const Vector3f& vec, float min, float max)
        {
            return Vector3f(math::min(math::max(vec.x, min), max), math::min(math::max(vec.y, min), max), math::min(math::max(vec.z, min), max));
        }

        static Vector3f reflect(const Vector3f& vec, const Vector3f& normal)
        {
            return vec - normal * dot(normal, vec) * 2.0f;
        }

        static Matrix4x4 *matrixMultiplication4_4(Matrix4x4 const *left, Matrix4x4 const *right){
            Matrix4x4 *returnValue = new Matrix4x4();
            for(int i = 0; i < 4; ++i){
                for(int j = 0; j < 4; ++j){
                    returnValue->matrix[i][j] = 0;
                    for(int k = 0; k < 4; ++k){
                            returnValue->matrix[i][j] += left->matrix[i][k] * right->matrix[k][j];
                    }
                }
            }
            return returnValue;
        }

        static Matrix4x4 *translationMatrix(double translateX, double translateY, double translateZ){

            Matrix4x4 *returnValue = new Matrix4x4();
            double translationMatrix[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
            translationMatrix[3] = translateX;
            translationMatrix[7] = translateY;
            translationMatrix[11] = translateZ;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    returnValue->matrix[i][j] = translationMatrix[i*4+j];
                }
            }
            return returnValue;
        }

        static Matrix4x1 *matrixMultiplication4_1(Matrix4x4 const *left,Matrix4x1 const *right){
            Matrix4x1 *returnValue = new Matrix4x1();
            for(int i = 0; i < 4; ++i){
                for(int j = 0; j < 1; ++j){
                    returnValue->matrix[i][j] = 0;
                    for(int k = 0; k < 4; ++k){
                            returnValue->matrix[i][j] += left->matrix[i][k] * right->matrix[k][j];
                    }
                }
            }
            return returnValue;
        }

        static Matrix4x4 *scaleMatrix(double scaleX, double scaleY, double scaleZ){
            //Matrix4x4 *translation1 = translationMatrix(-givenX,-givenY,-givenZ);
            //Matrix4x4 *translation2 = translationMatrix(givenX,givenY,givenZ);
            Matrix4x4 *scaleMatrix = new Matrix4x4();
            //Matrix4x4 *returnMatrix;
            //Matrix4x4 *temp;
            double scaleMatrixTemp[16] = {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
            scaleMatrixTemp[0] = scaleX;
            scaleMatrixTemp[5] = scaleY;
            scaleMatrixTemp[10] = scaleZ;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    scaleMatrix->matrix[i][j] = scaleMatrixTemp[i*4+j];
                }
            }
            //temp = matrixMultiplication4_4(scaleMatrix,translation1);
            //returnMatrix = matrixMultiplication4_4(translation2,temp);
            //delete translation1;
            //delete translation2;
            //delete scaleMatrix;
            //delete temp;
            return scaleMatrix;
        }


        static Matrix4x4 *rotationMatrix(double angle, double givenX, double givenY, double givenZ){
            Vector3f uVec = normalize(Vector3f(givenX,givenY,givenZ));
            Matrix4x4 *transform1 = new Matrix4x4();
            Matrix4x4 *transform2 = new Matrix4x4();
            Matrix4x4 *transform3 = new Matrix4x4();
            Matrix4x4 *returnMatrix;
            Matrix4x4 *temp;
            Vector3f vVec;
            Vector3f wVec;
            double absGivenX = std::abs(givenX);
            double absGivenY = std::abs(givenY);
            double absGivenZ = std::abs(givenZ);
            //std::cout << "Given: " << angle << " " << givenX <<" " <<givenY <<" " <<givenZ << std::endl;
            double minValue = math::min(absGivenX,absGivenY);
            minValue = math::min(minValue,absGivenZ);
            if(minValue == absGivenX){
                vVec = Vector3f(0,givenZ,-givenY);
            }
            else if(minValue == absGivenY){
                vVec = Vector3f(givenZ,0,-givenX);
            }
            else if(minValue == absGivenZ){
                vVec = Vector3f(givenY,-givenX,0);
            }
            wVec = cross(uVec,vVec);
            vVec = normalize(vVec);
            wVec = normalize(wVec);
            double ortho1[16] = {
                uVec.x, uVec.y, uVec.z, 0,
                vVec.x, vVec.y, vVec.z, 0,
                wVec.x, wVec.y, wVec.z, 0,
                0, 0, 0, 1
            };
            double ortho3[16] = {
                uVec.x,vVec.x,wVec.x,0,
                uVec.y,vVec.y,wVec.y,0,
                uVec.z,vVec.z,wVec.z,0,
                0,0,0,1
            };
            double cos = std::cos(angle*PI/180);
            double sin = std::sin(angle*PI/180);
            ////std::cout << "cos" << cos << std::endl;
            ////std::cout << "sin" << sin << std::endl;
            double xRotation[16] = {
                1,0,0,0,
                0,cos,-sin,0,
                0,sin,cos,0,
                0,0,0,1
            };
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    transform1->matrix[i][j] = ortho1[i*4+j];
                }
            }
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    transform2->matrix[i][j] = xRotation[i*4+j];
                }
            }
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    transform3->matrix[i][j] = ortho3[i*4+j];
                }
            }
            //std::cout << "--M matrix--" << std::endl;
            //std::cout << transform1->matrix[0][0] << " "<< transform1->matrix[0][1] << " "<< transform1->matrix[0][2] << " "<< transform1->matrix[0][3] << " " << std::endl;
            //std::cout << transform1->matrix[1][0] << " "<< transform1->matrix[1][1] << " "<< transform1->matrix[1][2] << " "<< transform1->matrix[1][3] << " " << std::endl;
            //std::cout << transform1->matrix[2][0] << " "<< transform1->matrix[2][1] << " "<< transform1->matrix[2][2] << " "<< transform1->matrix[2][3] << " " << std::endl;
            //std::cout << transform1->matrix[3][0] << " "<< transform1->matrix[3][1] << " "<< transform1->matrix[3][2] << " "<< transform1->matrix[3][3] << " " << std::endl;

            //std::cout << "--Rotation matrix--" << std::endl;
            //std::cout << transform2->matrix[0][0] << " "<< transform2->matrix[0][1] << " "<< transform2->matrix[0][2] << " "<< transform2->matrix[0][3] << " " << std::endl;
            //std::cout << transform2->matrix[1][0] << " "<< transform2->matrix[1][1] << " "<< transform2->matrix[1][2] << " "<< transform2->matrix[1][3] << " " << std::endl;
            //std::cout << transform2->matrix[2][0] << " "<< transform2->matrix[2][1] << " "<< transform2->matrix[2][2] << " "<< transform2->matrix[2][3] << " " << std::endl;
            //std::cout << transform2->matrix[3][0] << " "<< transform2->matrix[3][1] << " "<< transform2->matrix[3][2] << " "<< transform2->matrix[3][3] << " " << std::endl;

            //std::cout << "--M_inv matrix--" << std::endl;
            //std::cout << transform3->matrix[0][0] << " "<< transform3->matrix[0][1] << " "<< transform3->matrix[0][2] << " "<< transform3->matrix[0][3] << " " << std::endl;
            //std::cout << transform3->matrix[1][0] << " "<< transform3->matrix[1][1] << " "<< transform3->matrix[1][2] << " "<< transform3->matrix[1][3] << " " << std::endl;
            //std::cout << transform3->matrix[2][0] << " "<< transform3->matrix[2][1] << " "<< transform3->matrix[2][2] << " "<< transform3->matrix[2][3] << " " << std::endl;
            //std::cout << transform3->matrix[3][0] << " "<< transform3->matrix[3][1] << " "<< transform3->matrix[3][2] << " "<< transform3->matrix[3][3] << " " << std::endl;
            temp = matrixMultiplication4_4(transform3,transform2);
            returnMatrix = matrixMultiplication4_4(temp,transform1);
            //std::cout << "--returnMatrix--" << std::endl;
            //std::cout << returnMatrix->matrix[0][0] << " "<< returnMatrix->matrix[0][1] << " "<< returnMatrix->matrix[0][2] << " "<< returnMatrix->matrix[0][3] << " " << std::endl;
            //std::cout << returnMatrix->matrix[1][0] << " "<< returnMatrix->matrix[1][1] << " "<< returnMatrix->matrix[1][2] << " "<< returnMatrix->matrix[1][3] << " " << std::endl;
            //std::cout << returnMatrix->matrix[2][0] << " "<< returnMatrix->matrix[2][1] << " "<< returnMatrix->matrix[2][2] << " "<< returnMatrix->matrix[2][3] << " " << std::endl;
            //std::cout << returnMatrix->matrix[3][0] << " "<< returnMatrix->matrix[3][1] << " "<< returnMatrix->matrix[3][2] << " "<< returnMatrix->matrix[3][3] << " " << std::endl;
            delete transform1;
            delete transform2;
            delete transform3;
            delete temp;
            return returnMatrix;
        }

    }
}

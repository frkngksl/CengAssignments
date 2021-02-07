#pragma once

#include "camera.h"
#include "material.h"
#include "mesh.h"
#include "parser.h"
#include "point_light.h"
#include "ray.h"
#include "sphere.h"
#include "vector2f.h"
#include "vector3f.h"
#include "translation.h"
#include "scaling.h"
#include "rotation.h"
#include "texture.h"
#include "structObjects.h"
#include "jpeg.h"
#include <vector>

namespace fst
{
    struct Scene
    {
        //Data
        std::vector<Camera> cameras;
        std::vector<PointLight> point_lights;
        std::vector<Material> materials;
        std::vector<math::Vector3f> vertex_data;
        std::vector<math::Vector2f> tex_coord_data;
        std::vector<Mesh> meshes;
        std::vector<Sphere> spheres;
        std::vector<Translation> translations;
        std::vector<Scaling> scalings;
        std::vector<Rotation> rotations;
        std::vector<Texture> textures;
        math::Vector3f background_color;
        math::Vector3f ambient_light;
        float shadow_ray_epsilon;
        int max_recursion_depth;

        //Functions
        void setTransformMatrix(Matrix4x4 &givenMatrix,math::Vector3f &uVec, math::Vector3f &vVec, math::Vector3f &wVec, math::Vector3f &center);
        void applyOpSphere(const std::string &transformCode,math::Vector3f &center, double &radius,math::Vector3f &uVector,math::Vector3f &vVector, math::Vector3f &wVector);
        void doTransformSphere(const std::string &transformationString,math::Vector3f &center, double &radius,math::Vector3f &uVector,math::Vector3f &vVector, math::Vector3f &wVector);
        void applyOp(const std::string &transformCode, math::Vector3f &vertex0,math::Vector3f &vertex1, math::Vector3f &vertex2);
        void doTransformOperations(const std::string &transformationString,math::Vector3f &vertex0,math::Vector3f &vertex1, math::Vector3f &vertex2);
        void loadFromParser(const parser::Scene &parser);
        bool intersect(const Ray &ray, HitRecord &hit_record, float max_distance) const;
        bool intersectShadowRay(const Ray &ray, float max_distance) const;
    };
} // namespace fst

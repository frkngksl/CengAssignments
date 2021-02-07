#pragma once

#include "vector3f.h"
#include "structObjects.h"

namespace fst
{
    class Ray;
    struct HitRecord;

    class Sphere
    {
    public:
        Sphere(const math::Vector3f& center, float radius, int material_id,Matrix4x4 &transformMatrix,int textID);

        bool intersect(const Ray& ray, HitRecord& hit_record, float max_distance) const;
        bool intersectShadowRay(const Ray& ray, float max_distance) const;
        Matrix4x4 localMatrix;
        int textureID;
        math::Vector3f m_center;
        float m_radius;
        int m_material_id;
    };
}

#pragma once

#include "scene.h"
#include "structObjects.h"
namespace fst
{
    class Integrator
    {
    public:
        Integrator(const parser::Scene& parser);

        math::Vector3f renderPixel(const Ray& ray, int depth) const;
        void integrate() const;
        void getRGBValue(const Texture &ourTexture,double uParam, double vParam,ColorTexel &rgbValues) const;
        BaryParams calculateBarycetric(const Ray &givenRay,const math::Vector3f &vertex0,const math::Vector3f &vertex1,const math::Vector3f &vertex2) const;
        ColorTexel getUVCoordinates(const Ray &givenRay,math::Vector3f &intersectPoint,HitRecord &hitRecord) const;
    private:
        Scene m_scene;
    };
}

#include "material.h"
#include "vector3f.h"

#define REPLACEKD 0
#define BLENDKD 1
#define REPLACEALL 2


namespace fst
{
    Material::Material(const math::Vector3f& ambient, const math::Vector3f& diffuse, const math::Vector3f& specular, const math::Vector3f& mirror, float phong_exponent)
        : m_ambient(ambient)
        , m_diffuse(diffuse)
        , m_specular(specular)
        , m_mirror(mirror)
        , m_phong_exponent(phong_exponent)
    {}

    math::Vector3f Material::computeBrdf(const math::Vector3f& wi, const math::Vector3f& wo, const math::Vector3f& normal) const
    {
        //auto diffuse = math::max(math::dot(normal, wi), 0.0f);
        auto specular = std::pow(math::max(math::dot(math::normalize(wo + wi), normal), 0.0f), m_phong_exponent);

        return m_specular * specular;
    }
    math::Vector3f Material::computeBrdf2(const math::Vector3f& wi, const math::Vector3f& wo, const math::Vector3f& normal,ColorTexel &givenTexel) const
    {
        math::Vector3f newC;
        double cValue;
        auto diffuse = math::max(math::dot(normal, wi), 0.0f);
        //auto specular = std::pow(math::max(math::dot(math::normalize(wo + wi), normal), 0.0f), m_phong_exponent);
        if(givenTexel.red != -1 && givenTexel.green != -1 && givenTexel.blue != -1 && givenTexel.mode != 4){
            if(givenTexel.mode == REPLACEKD){
                cValue =  ((double)givenTexel.red)/255.0;
                newC.x = cValue;
                cValue =  ((double)givenTexel.green)/255.0;
                newC.y = cValue;
                cValue =  ((double)givenTexel.blue)/255.0;
                newC.z = cValue;
                return diffuse*newC;
            }
            else if(givenTexel.mode == BLENDKD){
                cValue =  (givenTexel.red)/255.0;
                newC.x = cValue;
                cValue =  (givenTexel.green)/255.0;
                newC.y = cValue;
                cValue =  (givenTexel.blue)/255.0;
                newC.z = cValue;
                newC.x = (newC.x+m_diffuse.x)/2;
                newC.y = (newC.y+m_diffuse.y)/2;
                newC.z = (newC.y+m_diffuse.z)/2;
                return diffuse * newC;
            }
            else if(givenTexel.mode == REPLACEALL){
                newC.x = givenTexel.red;
                newC.y = givenTexel.green;
                newC.z = givenTexel.blue;
                return newC;
            }
            return m_diffuse * diffuse;
        }
        else{
            return m_diffuse * diffuse;
        }
    }
}

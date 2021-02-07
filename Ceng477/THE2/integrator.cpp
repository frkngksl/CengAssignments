#include "integrator.h"
#include "image.h"
#include "ctpl_stl.h"
#include "structObjects.h"
#include <cmath>
#include <iostream>

#define REPLACEKD 0
#define BLENDKD 1
#define REPLACEALL 2

#define PI 3.14159265

namespace fst
{

    void Integrator::getRGBValue(const Texture &ourTexture,double uParam, double vParam,ColorTexel &rgbValues) const{
        if(ourTexture.m_appearance == "clamp"){
            if(uParam>1){
                uParam = 1;
            }
            else if(uParam < 0){
                uParam = 0;
            }
            if(vParam > 1){
                vParam = 1;
            }
            else if(vParam<0){
                vParam = 0;
            }
        }
        else if(ourTexture.m_appearance == "repeat"){
            uParam = uParam-std::floor(uParam);
            vParam = vParam-std::floor(vParam);
        }
        double imageCordi = uParam*ourTexture.m_width;
        double imageCordj = vParam*ourTexture.m_height;
        if(ourTexture.m_interpolation == "nearest"){
            int imageCordiInt = std::round(imageCordi);
            int imageCordjInt = std::round(imageCordj);
            rgbValues.red = ourTexture.m_image[(imageCordjInt*ourTexture.m_width+imageCordiInt)*3];
            rgbValues.green = ourTexture.m_image[(imageCordjInt*ourTexture.m_width+imageCordiInt)*3+1];
            rgbValues.blue = ourTexture.m_image[(imageCordjInt*ourTexture.m_width+imageCordiInt)*3+2];
        }
        else if(ourTexture.m_interpolation == "bilinear"){
            ColorTexel pqColor;
            ColorTexel pq1Color;
            ColorTexel p1qColor;
            ColorTexel p1q1Color;
            double rValue;
            double gValue;
            double bValue;
            int p = std::floor(imageCordi);
            int q = std::floor(imageCordj);
            double dx = imageCordi-p;
            double dy = imageCordj-q;
            pqColor.red = ourTexture.m_image[(q*ourTexture.m_width+p)*3];
            pqColor.green = ourTexture.m_image[(q*ourTexture.m_width+p)*3+1];
            pqColor.blue = ourTexture.m_image[(q*ourTexture.m_width+p)*3+2];

            pq1Color.red = ourTexture.m_image[((q+1)*ourTexture.m_width+p)*3];
            pq1Color.green = ourTexture.m_image[((q+1)*ourTexture.m_width+p)*3+1];
            pq1Color.blue = ourTexture.m_image[((q+1)*ourTexture.m_width+p)*3+2];

            p1qColor.red = ourTexture.m_image[(q*ourTexture.m_width+p+1)*3];
            p1qColor.green = ourTexture.m_image[(q*ourTexture.m_width+p+1)*3+1];
            p1qColor.blue = ourTexture.m_image[(q*ourTexture.m_width+p+1)*3+2];

            p1q1Color.red = ourTexture.m_image[((q+1)*ourTexture.m_width+p+1)*3];
            p1q1Color.green = ourTexture.m_image[((q+1)*ourTexture.m_width+p+1)*3+1];
            p1q1Color.blue = ourTexture.m_image[((q+1)*ourTexture.m_width+p+1)*3+2];

            rgbValues.red = pqColor.red*(1-dx)*(1-dy)+p1qColor.red*(dx)*(1-dy)+pq1Color.red*(1-dx)*(dy)+p1q1Color.red*(dx)*(dy);
            rgbValues.green = pqColor.green*(1-dx)*(1-dy)+p1qColor.green*(dx)*(1-dy)+pq1Color.green*(1-dx)*(dy)+p1q1Color.green*(dx)*(dy);
            rgbValues.blue = pqColor.blue*(1-dx)*(1-dy)+p1qColor.blue*(dx)*(1-dy)+pq1Color.blue*(1-dx)*(dy)+p1q1Color.blue*(dx)*(dy);
        }
        if(ourTexture.m_decalMode == "replace_kd" ){
            //std::cout << "Kullanildi Replace" << std::endl;
            rgbValues.mode = REPLACEKD;
        }
        else if(ourTexture.m_decalMode == "blend_kd"){
        //    std::cout << "Kullanildi blend" << std::endl;
            rgbValues.mode = BLENDKD;
        }
        else if(ourTexture.m_decalMode == "replace_all" ){
            //std::cout << "Kullanildi replaceall" << std::endl;
            rgbValues.mode = REPLACEALL;
        }
    }

    BaryParams Integrator::calculateBarycetric(const Ray &givenRay,const math::Vector3f &vertex0,const math::Vector3f &vertex1,const math::Vector3f &vertex2) const{
        double  a,b,c,d,e,f,g,h,i,j,k,l;
        double beta,gamma,alpha;
        BaryParams returnValue;
        double eimhf,gfmdi,dhmeg,akmjb,jcmal,blmkc;

        double determinantA;

        double dd;

        const math::Vector3f &ma = vertex0;
        const math::Vector3f &mb = vertex1;
        const math::Vector3f &mc = vertex2;

        a = ma.x-mb.x;
        b = ma.y-mb.y;
        c = ma.z-mb.z;

        d = ma.x-mc.x;
        e = ma.y-mc.y;
        f = ma.z-mc.z;

        g = givenRay.m_direction.x;
        h = givenRay.m_direction.y;
        i = givenRay.m_direction.z;

        j = ma.x-givenRay.m_origin.x;
        k = ma.y-givenRay.m_origin.y;
        l = ma.z-givenRay.m_origin.z;

        eimhf = e*i-h*f;
        gfmdi = g*f-d*i;
        dhmeg = d*h-e*g;
        akmjb = a*k-j*b;
        jcmal = j*c-a*l;
        blmkc = b*l-k*c;

        determinantA = a*eimhf+b*gfmdi+c*dhmeg;
        //if (determinantA==0) return -1; //deal

        //t = -(f*akmjb+e*jcmal+d*blmkc)/determinantA;

        //if (t<1.0) return -1;

        gamma = (i*akmjb+h*jcmal+g*blmkc)/determinantA;

        //if (gamma<0 || gamma>1){
        //    std::cout<<"Triangle Gamma hata " << gamma <<  std::endl;
        //}

        beta = (j*eimhf+k*gfmdi+l*dhmeg)/determinantA;

        //if (beta<0 || beta>(1-gamma)){
        //     std::cout<<"Triangle Beta hata" << std::endl;
        //}


        alpha = 1- gamma+ beta;
        returnValue.alpha = alpha;
        returnValue.beta = beta;
        returnValue.gamma = gamma;
        return returnValue;
    }

    ColorTexel Integrator::getUVCoordinates(const Ray &givenRay,math::Vector3f &intersectPoint,HitRecord &hitRecord) const{
        ColorTexel rgbValues;
        double uParam;
        double vParam;
        if(hitRecord.isSphere){
            Matrix4x1 *result;
            Matrix4x1 intPoint;
            const Sphere &hittedSphere = m_scene.spheres[hitRecord.indexOfItem];
            //rgbValues.mode = 4;
            if(hittedSphere.textureID == -1){
                rgbValues.red = -1;
                rgbValues.green = -1;
                rgbValues.blue = -1;
                return rgbValues;
            }
            const Texture &givenTexture = m_scene.textures[hittedSphere.textureID-1];
            double theta;
            double phi;
            intPoint.matrix[0][0] = intersectPoint.x;
            intPoint.matrix[1][0] = intersectPoint.y;
            intPoint.matrix[2][0] = intersectPoint.z;
            intPoint.matrix[3][0] = 1;
            result = math::matrixMultiplication4_1(&hittedSphere.localMatrix,&intPoint);
            theta = std::acos(result->matrix[1][0]/hittedSphere.m_radius);
            phi = std::atan2(result->matrix[2][0],result->matrix[0][0]);
            uParam = (-phi+PI)/(2*PI);
            vParam = theta/PI;
            delete result;
            getRGBValue(givenTexture,uParam,vParam,rgbValues);
            return rgbValues;
        }
        else{
            const Mesh &hittedMesh = m_scene.meshes[hitRecord.indexOfItem];
            const Triangle &hittedTriangle = hittedMesh.m_triangles[hitRecord.indexOfTriangle];
            ColorTexel rgbValues;
            if(hittedTriangle.textureID == -1){
                rgbValues.red = -1;
                rgbValues.green = -1;
                rgbValues.blue = -1;
                return rgbValues;
            }
            const Texture &ourTexture = m_scene.textures[hittedTriangle.textureID-1]; //doru
            int edgeIndex0 = hittedTriangle.edge0_textIndex; //doru
            int edgeIndex1 = hittedTriangle.edge1_textIndex; //doru
            int edgeIndex2 = hittedTriangle.edge2_textIndex; //doru
            const math::Vector2f &edge0uv = m_scene.tex_coord_data[edgeIndex0];
            const math::Vector2f &edge1uv = m_scene.tex_coord_data[edgeIndex1];
            const math::Vector2f &edge2uv = m_scene.tex_coord_data[edgeIndex2];
            BaryParams coordParams = calculateBarycetric(givenRay,hittedTriangle.m_v0,hittedTriangle.m_edge1 + hittedTriangle.m_v0,hittedTriangle.m_edge2 + hittedTriangle.m_v0);
            double uParam = edge0uv.x + coordParams.beta*(edge1uv.x-edge0uv.x)+coordParams.gamma*(edge2uv.x-edge0uv.x);
            double vParam = edge0uv.y + coordParams.beta*(edge1uv.y-edge0uv.y)+coordParams.gamma*(edge2uv.y-edge0uv.y);
            getRGBValue(ourTexture,uParam,vParam,rgbValues);
            return rgbValues;
        }
    }

    Integrator::Integrator(const parser::Scene& parser)
    {
        m_scene.loadFromParser(parser);
    }

    math::Vector3f Integrator::renderPixel(const Ray& ray, int depth) const
    {
        if (depth > m_scene.max_recursion_depth)
        {
            return math::Vector3f(0.0f, 0.0f, 0.0f);
        }

        HitRecord hit_record;
        auto result = m_scene.intersect(ray, hit_record, std::numeric_limits<float>::max());

        if (!result)
        {
            return m_scene.background_color;
        }

        auto& material = m_scene.materials[hit_record.material_id - 1];
        auto color = material.get_ambient() * m_scene.ambient_light;
        auto intersection_point = ray.getPoint(hit_record.distance);
        bool textureFlag = false;
        ColorTexel givenTextureColor = getUVCoordinates(ray,intersection_point,hit_record);

        for (auto& light : m_scene.point_lights)
        {
            auto to_light = light.get_position() - intersection_point;
            auto light_pos_distance = math::length(to_light);
            to_light = to_light / light_pos_distance;

            Ray shadow_ray(intersection_point + m_scene.shadow_ray_epsilon * to_light, to_light);

            if (!m_scene.intersectShadowRay(shadow_ray, light_pos_distance))
            {
                color = color + light.computeRadiance(light_pos_distance) * material.computeBrdf(to_light, -ray.get_direction(), hit_record.normal);
                if(givenTextureColor.mode == REPLACEALL){
                    color = color + material.computeBrdf2(to_light, -ray.get_direction(), hit_record.normal,givenTextureColor);
                }
                else{
                    color = color + light.computeRadiance(light_pos_distance) * material.computeBrdf2(to_light, -ray.get_direction(), hit_record.normal,givenTextureColor);
                }
            }
        }

        auto& mirror = material.get_mirror();
        if (mirror.x + mirror.y + mirror.z > 0.0f)
        {
            auto new_direction = math::reflect(ray.get_direction(), hit_record.normal);
            Ray secondary_ray(intersection_point + m_scene.shadow_ray_epsilon * new_direction, new_direction);

            return color + mirror * renderPixel(secondary_ray, depth + 1);
        }
        else
        {
            return color;
        }
    }

    void Integrator::integrate() const
    {
        for (auto& camera : m_scene.cameras)
        {
            auto& resolution = camera.get_screen_resolution();
            Image image(resolution.x, resolution.y);

            ctpl::thread_pool pool(128);
            for (int i = 0; i < resolution.x; ++i)
            {
                pool.push([i, &resolution, &camera, &image, this](int id) {
                    for (int j = 0; j < resolution.y; ++j)
                    {
                        auto ray = camera.castPrimayRay(static_cast<float>(i), static_cast<float>(j));

                        auto color = renderPixel(ray, 0);

                        image.setPixel(i, j, math::clamp(color, 0.0f, 255.0f));
                    }
                });
            }
            pool.stop(true);
            for(auto& texture: m_scene.textures){
                delete[] texture.m_image;
            }
            image.save(camera.get_image_name());
        }
    }
}

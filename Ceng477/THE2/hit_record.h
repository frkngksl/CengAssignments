#pragma once

#include "vector3f.h"

namespace fst
{
    struct HitRecord
    {
        math::Vector3f normal;
        float distance;
        int material_id;
        bool isSphere;
        int indexOfItem;
        int indexOfTriangle;
    };
}

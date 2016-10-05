#ifndef HITABLE_H
#define HITABLE_H

#include "ray.hpp"
//#include "material.h"
class material;

struct hit_record
{
    float t;    //parameter of where ray hits
    vec3 p;     //hitpoint
    vec3 normal;
    material* mat;
};

class hitable
{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif

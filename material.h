#ifndef MATERIAL_H
#define MATERIAL_H

#include<glm/glm.hpp>
#include "ray.hpp"
#include "hitable.h"
class material
{
public:
    //Pure virtual function
    virtual bool scatter(const ray& r, const hit_record& rec, vec3& attentuation, ray& scattered) const = 0;

}

#endif

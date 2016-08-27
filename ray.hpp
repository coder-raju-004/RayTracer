#ifndef RAY_HPP
#define RAY_HPP

#include<glm/vec3.hpp>

using namespace glm;

class ray{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b){A = a; B = b;}
        vec3 origin() const     {return A;}
        vec3 direction() const  {return B;}
        vec3 point_at_parameter(float t) const {return A + B*t;}

    private:
        vec3 A;
        vec3 B;
};

#endif

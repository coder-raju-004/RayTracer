#ifndef CAMERA_H 
#define CAMERA_H 

#include "ray.hpp"

class Camera 
{
    private:
        glm::vec3 lower_left_corner;
        glm::vec3 origin;
        glm::vec3 horizontal;
        glm::vec3 vertical;

    public:
        Camera() 
        {
            lower_left_corner = glm::vec3(-2.0f, -1.0f, -1.0f);
            horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
            vertical = glm::vec3(0.0f, 2.0f, 0.0f);
            origin = glm::vec3(0.0f);
        }

        ray get_ray(float u, float v)
        {
            return ray(origin, lower_left_corner + horizontal*u + vertical*v - origin); 
        } 

};

#endif

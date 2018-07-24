#define GLM_ENABLE_EXPERIMENTAL
#include<iostream>
#include<limits>
#include<fstream>
#include<random>
#include<glm/glm.hpp>
#include<glm/gtx/norm.hpp>
#include "ray.hpp"
#include "hitable_list.hpp"
#include "sphere.hpp"
#include "camera.h"

using namespace std;

glm::vec3 random_point_in_unit_sphere()
{
    glm::vec3 p;
    p = 2.0f*(glm::vec3(drand48(), drand48(), drand48())) - glm::vec3(1.0f);
//    do
//    {
//        p = 2.0f*glm::vec3(drand48(), drand48(), drand48()) - vec3(1.0f);
//    }
//    while(length2(p) >= 1.0f);
//    cout<<length(p)<<" ";
    return p;
}

glm::vec3 color(const ray& r, hitable *world, int numBounces)
{
    hit_record rec;
    if((numBounces>0) && world->hit(r, 0.001, numeric_limits<float>::max(), rec))
    {
        glm::vec3 target = rec.p + rec.normal + random_point_in_unit_sphere();
        return 0.5f*color(ray(rec.p, target - rec.p), world, numBounces - 1); 
        //0.5f*glm::vec3(rec.normal.x + 1.0f, rec.normal.y + 1.0f, rec.normal.z + 1.0f);
    }
    else
    {
        glm::vec3 unit_direction = normalize(r.direction());
        float t = 0.5*(unit_direction.y + 1.0);

        //return blend between blue and white
        return (1.0f-t)*glm::vec3(1.0f) + t*glm::vec3(0.5f, 0.7f, 1.0f);
    }
}

int main()
{
    ofstream fout;
    fout.open("picture.ppm");

    int nx=800;     //x-resolution
    int ny=400;     //y-resolution
    int ns = 50;   //number of samples per pixel

    fout<<"P3\n"<< nx << " " << ny << "\n255\n";
    glm::vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    glm::vec3 horizontal(4.0f, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, 2.0f, 0.0f);
    glm::vec3 origin(0.0f);

    hitable *list[2];
    list[0] = new sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100.0);
    list[1] = new sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5);

    hitable *world = new hitable_list(list, 2);

    Camera cam;
    for(int j=ny-1; j>=0; j--)
    {
        for(int i=0;i < nx; ++i)
        {
            //Take multiple samples per pixel, for antialiasing
            glm::vec3 col = glm::vec3(0.0f, 0.0f, 0.0f);
            for(int sample = 0; sample < ns; ++sample)
            {
                float u = float(i + drand48())/float(nx);
                float v = float(j + drand48())/float(ny);
                ray r=cam.get_ray(u, v);
                //color takes a ray, a world, and tells us color of where it hits
                col += color(r, world, 50);

            }
            col /= float(ns);
            int ir = int(255.99*col.r);
            int ig = int(255.99*col.g);
            int ib = int(255.99*col.b);
            fout<< ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

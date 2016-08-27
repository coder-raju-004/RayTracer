#include<iostream>
#include<fstream>
#include<glm/glm.hpp>
#include<glm/vec3.hpp>
#include "ray.hpp"

using namespace std;
using namespace glm;

float hit_sphere(const vec3& center, float radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f*dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;

    float discrimiant = (b*b - 4*a*c);
    if(discrimiant < 0)
    {
        return -1.0f;
    }
    else
    {
        return (-b - sqrt(discrimiant))/(2.0f*a);
    }
}

vec3 color(const ray& r)
{
    float t = hit_sphere(vec3(0.0f, 0.0f, -2.0f), 0.5f, r);
    if(t > 0.0f)
    {
        vec3 normal = normalize(r.point_at_parameter(t) - vec3(0.0f, 0.0f, -2.0f));
        return 0.5f*vec3(normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f);
    }
    vec3 unit_dir = normalize(vec3(r.direction()));
    t = 0.5f*(unit_dir.y + 1.0f);
    //return blend between blue and white
    return (1.0f-t)*vec3(1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
    ofstream fout;
    fout.open("picture.ppm");

    int nx=300;
    int ny=150;
    fout<<"P3\n"<< nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f);

    for(int j=ny-1; j>=0; j--)
    {
        for(int i=0;i < nx; ++i)
        {
            float u = float(i)/float(nx);
            float v = float(j)/float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            vec3 col = color(r);
            int ir = int(255.99*col.r);
            int ig = int(255.99*col.g);
            int ib = int(255.99*col.b);
            fout<< ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

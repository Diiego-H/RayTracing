#include "Metal.hh"

Metal::Metal(const vec3& color): Material()
{
    Kd = color;
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

Metal::Metal(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {
}

Metal::~Metal()
{
}

bool Metal::scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const  {
    auto rec = r_in.getHit(t);
    vec3 target = reflect(r_in.getDirection(),rec->normal);
    
    r_out =  Ray(rec->p, target);
    color = Ks;
    return true;
}

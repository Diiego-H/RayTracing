#pragma once

#include "Material.hh"

class Transparent : public Material
{

public:
    Transparent() {};
    Transparent(const vec3& color);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k);
    Transparent(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    virtual ~Transparent();

    virtual bool scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const;

};

#pragma once

#include "Material.hh"
#include "Texture.hh"

class MaterialTextura : public Material
{

private:
    shared_ptr<Texture> textura;
    QString textureFile;

public:
    MaterialTextura() {};
    MaterialTextura(const vec3& color);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k);
    MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o);
    virtual ~MaterialTextura();

    virtual bool scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const;
    virtual vec3 getDiffuse(vec2 point) const;

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;
};

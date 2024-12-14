#pragma once

#include "Rays/Ray.hh"
#include "Rays/Hittable.hh"
#include "DataService/Serializable.hh"

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater implementat
class Material: public Serializable
{
public:

    Material();
    Material(vec3 d);
    Material(vec3 a, vec3 d, vec3 s, float shininess);
    Material(vec3 a, vec3 d, vec3 s, float shininess, float opacity);
    ~Material();

    virtual bool scatter(const Ray& r_in, int t, vec3& color, Ray & r_out) const = 0;
    virtual vec3 getDiffuse(vec2 point) const;

    vec3 Ka;
    vec3 Kd;
    vec3 KdToon[4];
    vec3 Ks;
    vec3 Kt;

    float shininess;
    float opacity; // opacity es la fraccio de 0..1 (0 és totalment transparent, 1 és totalment opac)
    float nut; // índex de refracció del material
    float dmax; // distancia màxima que pot atravessar la llum

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;

};



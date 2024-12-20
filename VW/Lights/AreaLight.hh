#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "Light.hh"

#include "glm/gtx/norm.hpp"

class AreaLight: public Light {
public:
    AreaLight() {};
    /*
     * Constructor de la classe AreaLight.
     * param posicio: posició de la llum.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * param a: coeficient a de l'atenuacio.
     * param b: coeficient b de l'atenuacio.
     * param c: coeficient c de l'atenuacio.
     * param radius: radi del llum.
     * */
    AreaLight(vec3 posicio, vec3 Ia, vec3 Id, vec3 Is, float a, float b, float c, float radius);
    virtual ~AreaLight() {}
    vec3 getPos();
    virtual vec3 vectorL(vec3 point) override;
    virtual float attenuation(vec3 point) override;
    virtual float distanceToLight(vec3 point) override;
    virtual vec3 getRandomPointOnLight();

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;
private:
    vec3 pos;
    float a; // atenuacio: terme constant
    float b; // atenuacio: terme lineal
    float c; // atenuacio: terme quadratic
    float radius;
};

#endif // AREALIGHT_H

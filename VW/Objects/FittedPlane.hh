#pragma once

#include "Plane.hh"
#include "../TG/TranslateTG.hh"


class FittedPlane: public Plane {
public:
    FittedPlane() {}
    FittedPlane(vec3 normal, vec3 pass_point, const vec2 &min, const vec2 &max);
    virtual ~FittedPlane(){}

    virtual bool hit(Ray &r, float tmin, float tmax) const override;
    virtual bool allHits(Ray& r, float tmin, float tmax) const override;

    virtual void update(int nframe) override {}
    virtual void aplicaTG(shared_ptr<TG> tg) override {}

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

private:
    void computeAttributes();
    vec2 pmin;
    vec2 pmax;

    // Precomputed to reduce execution time
    float w;
    float h;
    int w_component;
    int h_component;
    vec3 origin;
};



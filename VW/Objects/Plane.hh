#pragma once

#include "Object.hh"
#include "../TG/TranslateTG.hh"


class Plane: public Object {
public:
    Plane() {};
    Plane(vec3 normal, vec3 pass_point);
    Plane(vec3 normal, float d);
    Plane(vec3 normal, vec3 pass_point, float d, shared_ptr<Material> m);

    virtual ~Plane(){}
    virtual bool hit(Ray &r, float tmin, float tmax) const override;
    virtual bool allHits(Ray& r, float tmin, float tmax) const override;

    virtual void update(int nframe) override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    bool isIntersection(float *t, vec3 origin, vec3 direction, float tmin, float tmax) const;
    bool isNormal(vec3 normal) const;
    bool isD(float d) const;

    vec3 getNormal() const;

protected:
    void computeD();
    vec3 normal;
    vec3 v1;

private:
    float D;
};



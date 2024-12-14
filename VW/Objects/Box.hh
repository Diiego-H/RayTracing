/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#pragma once

#include "Object.hh"
#include "../TG/TranslateTG.hh"


class Box: public Object  {
public:
    Box();
    Box(const vec3 &min, const vec3 &max);

    virtual ~Box() {}
    virtual bool hit(Ray& r, float tmin, float tmax) const override;
    virtual bool allHits(Ray& r, float tmin, float tmax) const override;

    virtual void update(int nframe) override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;


private:
    // Minimum box point
    vec3 min;
    // Maximum box point
    vec3 max;
};






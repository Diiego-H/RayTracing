/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#pragma once

#include "Sphere.hh"
#include "../TG/TranslateTG.hh"

class EnvironmentalSphere: public Sphere {
public:
    EnvironmentalSphere();
    EnvironmentalSphere(vec3 cen, float r);
    virtual ~EnvironmentalSphere() {}

    virtual void read (const QJsonObject &json) override;

protected:
    virtual vec2 project(vec3 p) const;
};

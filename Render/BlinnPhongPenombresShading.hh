#pragma once

#include "BlinnPhongShading.hh"

#define shadowRayNumber 10; 

class BlinnPhongPenombresShading: public BlinnPhongShading
{
public:
    BlinnPhongPenombresShading() {};
    virtual float computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene) override;
    ~BlinnPhongPenombresShading(){};
};


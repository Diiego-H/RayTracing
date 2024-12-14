#pragma once

#include "ShadingStrategy.hh"

class BlinnPhongShading: public ShadingStrategy
{
public:
    BlinnPhongShading() {};
    vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, 
                 vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow) override;
    ~BlinnPhongShading(){};
};


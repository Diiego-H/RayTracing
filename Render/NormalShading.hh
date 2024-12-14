#pragma once

#include "ShadingStrategy.hh"

class NormalShading: public ShadingStrategy
{
public:
    NormalShading() {};
    vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, 
                 vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow) override;
    ~NormalShading(){};
};


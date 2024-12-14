#pragma once

#include "Scene.hh"
#include "Light.hh"
class ShadingStrategy {
 public:
    // TODO: Fase 2: Canviar el mètode per passar les llums per calcular el shading
    virtual vec3 shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> info, vec3 lookFrom, 
                         vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow) 
    {
        return vec3(0.0, 0.0, 0.0);
    };

    // TUTORIAL 2: Calcula si el punt "point" és a l'ombra segons si el flag està activat o no
    // Afegit el paràmetre scene per poder calcular si el punt està a l'ombra o no
    virtual float computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene);

    virtual ~ShadingStrategy() {};
};

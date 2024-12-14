#include "ColorShading.hh"

vec3 ColorShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom,
                           vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow)
{
    if (!infos.empty())
    {
        // En cas que no sigui buit ens hem de fixar si estem tenint en compte les ombres o no
        // Si no hi ha ombra es retorna la component difosa del material
        vec3 componentDifosa = infos[0]->mat->Kd;
        if (shadow)
        {
            // Si per configuració tenim les ombres activades mirarem si el punt està a l'ombra
            auto p = infos[0]->p;

            // Component ambient
            vec3 Ka = infos[0]->mat->Ka;
            vec3 componentAmbient(0.0);

            // Acumularem el factor ombra i en farem la mitjana aritmètica
            float cummulShadowFactor = 0.0f;
            if (lights.size() > 0) {
                // Anem a fer la mitjana aritmètica dels shadowFactor de les llums
                for (shared_ptr<Light> l : lights)
                {
                    cummulShadowFactor += computeShadow(l, p, scene); // Retorna 1.0 si no té ombra
                    componentAmbient += Ka * l->getIa();
                }
                cummulShadowFactor = cummulShadowFactor / lights.size();
            }

            // Interpolem el color amb la component ambient
            return cummulShadowFactor * componentDifosa + (1 - cummulShadowFactor) * componentAmbient;
        }
        else
        {
            return componentDifosa;
        }
    }
    else
    {
        // Tracta la situació on el vector infos és buit
        // Retorna un valor predeterminat o maneja-ho segons les teves necessitats.
        return vec3(0.0f);
    }
}

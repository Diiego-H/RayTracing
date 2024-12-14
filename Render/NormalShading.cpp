#include "NormalShading.hh"

vec3 NormalShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom,
                            vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow)
{
    if (!infos.empty())
    {
        // Color que es retornarà en cas que no hi hagi ombra
        vec3 color = 0.5f * (infos[0]->normal + 1.0f);

        // En cas que no sigui buit ens hem de fixar si estem tenint en compte les ombres o no
        if (shadow)
        {
            // Si per configuració tenim les ombres activades mirarem si el punt està a l'ombra
            auto p = infos[0]->p;

            // Component ambient
            vec3 Ka = infos[0]->mat->Ka;
            vec3 componentAmbient(0.0);

            float cummulShadowFactor = 0.0f;
            if (lights.size() > 0) {
                // Anem a fer la mitjana aritmètica dels shadowFactor de les llums
                for (shared_ptr<Light> l : lights)
                {
                    cummulShadowFactor += computeShadow(l, p, scene); // Sumem el factor ombra de cada llum
                    componentAmbient += Ka * l->getIa();
                }
                cummulShadowFactor = cummulShadowFactor / lights.size();
            }

            // Interpolem el color amb la component ambient
            return cummulShadowFactor * color + (1 - cummulShadowFactor) * componentAmbient;
        }
        else
        {
            // Si no estem tenint en compte les ombres retornem el color de la normal
            return color;
        }
    }
    else
    {
        // Tracta la situació on el vector infos és buit
        // Retorna un valor predeterminat o maneja-ho segons les teves necessitats.
        return vec3(0.0f);
    }
}

#include "NColorShading.hh"


vec3 NColorShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, 
                            vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow)
{
    if (!infos.empty()) {
        vec3 color(0.0f);
        vec3 factor(1.0f);
        for (shared_ptr<HitRecord> h : infos) {
            auto m = h->mat;
            color += (1.0f - m->Kt) * factor * m->Kd;
            factor *= m->Kt;
        }
        return color;
    } else {
        // Tracta la situació on el vector infos és buit
        // Retorna un valor predeterminat o maneja-ho segons les teves necessitats.
        return vec3(0.0f);
    }
}

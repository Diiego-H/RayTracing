#include "CelShading.hh"


vec3 CelShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, 
                           vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow)
{
    vec3 color(0.0f);

    if (!infos.empty()) {
        // En cas que no sigui buit ens hem de fixar si estem tenint en compte les ombres o no
        shared_ptr<HitRecord> hit = infos[0];
        vec3 hitPoint = hit->p;
        vec3 V = normalize(lookFrom - hitPoint);
        auto m = hit->mat;
        vec3 Ka = m->Ka;
        vec3 *Kds = m->KdToon;
        vec3 Kd0 = Kds[0];
        vec3 Ks = m->Ks;
        vec3 normal = hit->normal;
        float shininess = m->shininess;

        if (shadow) {
            for (shared_ptr<Light> l : lights) {
                vec3 lightColor(0.0f);
                vec3 L = l->vectorL(hitPoint);

                // Discretització intensitat
                float cosDif = glm::max(dot(L, normal), 0.0f);
                int i;
                if (cosDif > 0.95) { i=0; }
                else if (cosDif > 0.5) { i=1; }
                else if (cosDif > 0.25) { i=2; }
                else { i=3; }

                // Component difosa
                lightColor += Kds[i] * l->getId();

                // Component especular
                float cosEsp = dot(normalize(L + V), normal);
                if (cosEsp > 0.995) {
                    lightColor += Kd0 * l->getIs() * pow(0.99f, shininess);
                }

                // Rim shading
                lightColor += Kd0 * Ks * ((1 - dot(V, normal)) > 0.9f ? 1.0f : 0.0f) * cosDif;

                // Factor d'ombra
                lightColor *= computeShadow(l,hitPoint,scene);

                // Component ambient
                lightColor += Ka * l->getIa();

                color += lightColor;
            }
        } else {
            for (shared_ptr<Light> l : lights) {
                vec3 lightColor(0.0f);
                vec3 L = l->vectorL(hitPoint);

                // Discretització intensitat
                float cosDif = glm::max(dot(L, normal), 0.0f);
                int i;
                if (cosDif > 0.95) { i=0; }
                else if (cosDif > 0.5) { i=1; }
                else if (cosDif > 0.25) { i=2; }
                else { i=3; }

                // Component difosa
                lightColor += Kds[i] * l->getId();

                // Component especular
                float cosEsp = dot(normalize(L + V), normal);
                if (cosEsp > 0.995) {
                    lightColor += Kd0 * l->getIs() * pow(0.99f, shininess);
                }

                // Rim shading
                lightColor += Kd0 * Ks * ((1 - dot(V, normal)) > 0.9f ? 1.0f : 0.0f) * cosDif;

                // Component ambient
                lightColor += Ka * l->getIa();

                color += lightColor;
            }
        }

        // Llum global
        color += globalLight * Ka;
    }
    
    return color;
}

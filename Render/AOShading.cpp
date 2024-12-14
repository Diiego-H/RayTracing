#include "AOShading.hh"

vec3 AOShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, 
                                vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow) 
{
    // Si aquest raig te algun Hit.
    if (!infos.empty())
    {
        // S'han extret totes les variables que es necessiten a ambdós casos
        shared_ptr<HitRecord> firstHit = infos[0];
        vec3 hitPoint = firstHit->p;
        vec3 V = lookFrom - hitPoint;
        auto m = firstHit->mat;
        vec3 Ka = m->Ka;
        vec3 Kd = m->Kd;
        vec3 Ks = m->Ks;
        vec3 result = vec3(0);
        float shininess = m->shininess;
        vec3 normal = firstHit->normal;

        // Si tenim les ombres activades
        if(shadow){

            // Precalculem la Ambient occlussion local i global
            #define RTAO_SAMPLES 32  // TODO: agafar les samples d'algun parametre?
            #define GLOBAL_AO_MAX 100.0f
            #define LOCAL_AO_MAX 1.0f
            #define VECTOR_UP vec3(0.0f,1.0f,0.0f)
            int numHits = 0;
            // Local ambient occlussion
            for (int i = 0; i < RTAO_SAMPLES; i++)
            {
                // volem vectors en la semiesfera superior segons el pla tangent
                // per tant si esta en la inferior (contrari a la normal), el girem
                vec3 dir = sphericalRand(1.0f);
                if(dot(firstHit->normal, dir) < 0.0f) {
                    dir = -dir;
                }
                Ray auxAO(hitPoint, dir, 0.01f);
                if(scene->hit(auxAO, 0.01f, LOCAL_AO_MAX)) {
                    numHits += 1;
                }
            }
            float localAOFactor = 1.0f - ((float)numHits / RTAO_SAMPLES);

            // Global ambient occlussion
            // faltaria definir que es el "cel" i cap on tirar els rajos
            // en cas de outdoor
            numHits = 0;
            for (int i = 0; i < RTAO_SAMPLES; i++)
            {
                // volem vectors en la semiesfera superior segons el pla tangent
                // per tant si esta en la inferior (contrari a la normal), el girem
                vec3 dir = sphericalRand(1.0f);
                if(dot(VECTOR_UP, dir) < 0.0f) {
                    dir = -dir;
                }
                Ray auxAO(hitPoint, dir, 0.01f);
                if(scene->hit(auxAO, 0.01f, GLOBAL_AO_MAX)) {
                    numHits += 1;
                }
            }
            float globalAOFactor = 1.0f - ((float)numHits / RTAO_SAMPLES);

            // Iterem pels llums.
            for (shared_ptr<Light> lightPtr : lights)
            {
                // Calculem el factor d'ombra en aquell punt
                float shadowFactor = computeShadow(lightPtr, hitPoint, scene);

                // Llum difosa.
                vec3 L = lightPtr->vectorL(hitPoint);
                // Calculem el cosinus de l'angle entre L i el vector normal al punt de tall.
                // No cal dividir entre el producte de normes ja que els vectors ja estan normalitzats.
                float cosDif = dot(L, normal);

                vec3 resultAtenuable = (lightPtr->getId() * Kd * std::max(cosDif, 0.0f));

                // Llum especular.
                vec3 H = normalize(L + V);
                // Calculem el cosinus de l'angle entre H i el vector normal al punt de tall.
                // No cal dividir entre el producte de normes ja que els vectors ja estan normalitzats.
                float cosEspec = dot(H, normal);

                resultAtenuable += lightPtr->getIs() * Ks * pow(std::max(cosEspec, 0.0f), shininess);

                // Atenuacio.
                resultAtenuable *= lightPtr->attenuation(hitPoint);

                // Apliquem el factor d'ombra a la suma de llum difosa i especular
                resultAtenuable *= shadowFactor;

                // Llum ambient.
                result += resultAtenuable + (lightPtr->getIa() * Ka * localAOFactor);
            }
            // Llum global.
            return result + globalLight * Ka * globalAOFactor;
        }
        else{
            // Iterem pels llums.
            for (shared_ptr<Light> lightPtr : lights)
            {
                // Llum difosa.
                vec3 L = lightPtr->vectorL(hitPoint);
                // Calculem el cosinus de l'angle entre L i el vector normal al punt de tall.
                // No cal dividir entre el producte de normes ja que els vectors ja estan normalitzats.
                float cosDif = dot(L, normal);

                vec3 resultAtenuable = (lightPtr->getId() * Kd * std::max(cosDif, 0.0f));

                // Llum especular.
                vec3 H = normalize(L + V);
                // Calculem el cosinus de l'angle entre H i el vector normal al punt de tall.
                // No cal dividir entre el producte de normes ja que els vectors ja estan normalitzats.
                float cosEspec = dot(H, normal);

                resultAtenuable += lightPtr->getIs() * Ks * pow(std::max(cosEspec, 0.0f), shininess);

                // Atenuacio.
                resultAtenuable *= lightPtr->attenuation(hitPoint);

                // Llum ambient.
                result += resultAtenuable + (lightPtr->getIa() * Ka);
            }
            // Llum global.
            return result + globalLight * Ka;
        }
    }
    else
    {
        // Si no hi ha hits, retornar zero color.
        return vec3(0.0f);
    }
}

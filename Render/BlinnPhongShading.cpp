#include "BlinnPhongShading.hh"

vec3 BlinnPhongShading::shading(shared_ptr<Scene> scene, vector<shared_ptr<HitRecord>> infos, vec3 lookFrom, 
                                vec3 globalLight, vector<shared_ptr<Light>> lights, bool shadow) 
{
    // Si aquest raig te algun Hit.
    if (!infos.empty())
    {
        // S'han extret totes les variables que es necessiten a ambdós casos
        shared_ptr<HitRecord> firstHit = infos[0];
        vec3 hitPoint = firstHit->p;
        vec3 V = normalize(lookFrom - hitPoint);
        auto m = firstHit->mat;
        vec3 Ka = m->Ka;
        vec3 Kd = m->getDiffuse(firstHit->uv);
        vec3 Ks = m->Ks;
        vec3 result = vec3(0);
        float shininess = m->shininess;
        vec3 normal = firstHit->normal;

        // Si tenim les ombres activades
        if(shadow){

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
                result += resultAtenuable + lightPtr->getIa() * Ka;
            }
            // Llum global.
            return result + globalLight * Ka;
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

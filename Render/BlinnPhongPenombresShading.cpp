#include "BlinnPhongPenombresShading.hh"
#include "AreaLight.hh"

float BlinnPhongPenombresShading::computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene)
{
    // Si el llum és de tipus AreaLight, volem calcular penombres.
    if (auto areaLight = dynamic_pointer_cast<AreaLight>(light))
    {
        int numRays = shadowRayNumber;

        int raysWithoutShadow = 0;

        for (int i = 0; i < numRays; ++i)
        {
            // Genera un punt aleatori al llum
            vec3 randomPointOnLight = areaLight->getRandomPointOnLight();

            // Calculem el vector que va del punt al punt aleatori al llum.
            vec3 vectorL = randomPointOnLight - point;

            // Creem el ray.
            Ray shadowRay(point, vectorL);
            float tmax = glm::length(vectorL);

            // Comprovem si hi ha algun hit.
            if (!scene->hit(shadowRay, shadowRay.getTmin(), tmax))
            {
                raysWithoutShadow++;
            }
        }

        // Calculem el percentatge de rajos sense ombra i el retornem.
        float softShadowPercentage = static_cast<float>(raysWithoutShadow) / static_cast<float>(numRays);

        return softShadowPercentage;
    }
    else
    {
        // Ombra de llum puntual.
        vec3 vectorL = light->vectorL(point);
        Ray shadowRay(point, vectorL);
        float tmax = light->distanceToLight(point);

        // tmax marca la distància entre el punt i la llum i ens servirà per a calcular si hi ha alguna intersecció
        // Tmin és per defecte 0.01 i així ja evitem que el raig intersequi amb el mateix objecte (shadow acne)
        if (scene->hit(shadowRay, shadowRay.getTmin(), tmax))
        {
            return 0.0f;
        }
        else
        {
            return 1.0f;
        }
    }
}

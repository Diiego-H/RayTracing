#include "ShadingStrategy.hh"

float ShadingStrategy::computeShadow(shared_ptr<Light> light, vec3 point, shared_ptr<Scene> scene)
{
    // Hem de calcular si el punt és a l'ombra o no
    // El punt en qüestió és point i disposem de la llum light
    // Per a calcular-ho obtindrem el raig que passa per la llum i pel punt
    // Comprovarem si hi ha alguna intersecció amb algun objecte de l'escena abans d'arribar a la llum

    vec3 vectorL = light->vectorL(point);
    Ray shadowRay(point, vectorL);
    float tmax = light->distanceToLight(point);
    float tmin = shadowRay.getTmin();

    // tmax marca la distància entre el punt i la llum i ens servirà per a calcular si hi ha alguna intersecció
    // Tmin és per defecte 0.01 i així ja evitem que el raig interseci amb el mateix objecte (shadow acne)

    // Inicialitzem el factor ombra a 1.0f
    float shadowFactor = 1.0f;

    // Anem a veure si hi ha alguna intersecció
    if (scene->allHits(shadowRay, tmin, tmax))
    {
        // Per començar volem obtenir el HitRecord del raig que ha intersecat amb l'escena
        vector<shared_ptr<HitRecord>> hits = shadowRay.getHitRecords();

        int n = hits.size();
        int i = 0;

        // Per obtenir ombres transparents, prendrem 2 interseccions per objecte entre el punt i la llum
        // SUPOSEM PER TANT QUE SEMPRE TENIM 2 INTERSECCIONS PER OBJECTE tret de, potser, la primera
        // intersecció (cas que computem l'ombra d'un punt d'una esfera, per exemple).
        if ((n % 2) != 0) {
            // Primera intersecció
            shared_ptr<HitRecord> hit = shadowRay.getHit(0);
            float d = hit->t - tmin; // Distància del raig atravessant l'objecte
            float dmax = hit->mat->dmax; // Distància màxima que pot atravessar la llum al material

            // Actualització factor ombra en funció de dmax del material
            if (d > dmax || dmax < DBL_EPSILON) {
                return 0.0f;    // No passa llum
            }      
            shadowFactor *= (1 - d / dmax);
            if (shadowFactor < DBL_EPSILON)
                return 0.0f; // Factor prou proper a 0, parem d'iterar

            // Processem les interseccions a parelles a partir de la següent
            i = 1;
        }
        for (i; i < n-1; i += 2)
        {
            // Com que tenim que el vector director del raig de la llum és normal, es tracta de mirar les t dels hits
            shared_ptr<HitRecord> hit1 = shadowRay.getHit(i);
            shared_ptr<HitRecord> hit2 = shadowRay.getHit(i + 1);
            float d = hit2->t - hit1->t;  // Distància del raig atravessant l'objecte
            float dmax = hit1->mat->dmax; // Distància màxima que pot atravessar la llum

            // Actualització factor ombra en funció de dmax del material
            if (d > dmax || dmax < DBL_EPSILON) {
                return 0.0f;    // No passa llum
            }    
            shadowFactor *= (1 - d / dmax);
            if (shadowFactor < DBL_EPSILON)
                return 0.0f; // Factor prou proper a 0, parem d'iterar
        }
    }

    return shadowFactor;
}

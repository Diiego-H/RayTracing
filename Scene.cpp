#include "Scene.hh"

Scene::Scene() {
    pmin.x = -0.5f;
    pmin.y = -0.5f;
    pmin.z = -0.5f;
    pmax.x = 0.5f;
    pmax.y = 0.5f;
    pmax.z = 0.5f;
}

bool Scene::hit(Ray &raig, float tmin, float tmax) const {
    // TO DO TUTORIAL 0 i TUTORIAL 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb la interseccio
    // mes propera a l'observador, en el cas que n'hi hagi més d'una.
    // Si un objecte es intersecat pel raig, cal actualitzar la llista de  HitRecords que conte el raig

    // Interseccions amb els objectes de l'escena
    Ray aux(raig.getOrigin(), raig.getDirection(), tmin, tmax);
    bool any = false;
    for (shared_ptr<Object> o : objects) {
        any |= o->hit(aux, tmin, tmax);
    }

    // Intersecció més propera
    float min = tmax;
    for (shared_ptr<HitRecord> h : aux.getHitRecords()) {
        if (h->t < min) {
            min = h->t;
            raig.addHit0(h);
        }
    }

    return any;
}

bool Scene::allHits(Ray &r, float tmin, float tmax) const {
    // TO DO TUTORIAL 0 i TUTORIAL 1:
    // Heu de codificar la vostra solucio per aquest metode substituint el 'return true'
    // Una possible solucio es cridar el mètode "hit" per a tots els objectes i quedar-se amb totes
    // les interseccions
    // Si un objecte es intersecat pel raig, el parametre  de tipus HitRecord conte
    // la informació sobre la interseccio.
    // Cada vegada que s'intersecta un objecte s'ha d'afegir un nou HitRecord del raig.

    // Interseccions amb els objectes de l'escena
    bool any = false;
    for (shared_ptr<Object> o : objects) {
        any |= o->allHits(r, tmin, tmax);
    }
    return any;
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i < objects.size(); i++) {
        objects[i]->update(nframe);
    }
}

void Scene::setDimensions(vec3 p1, vec3 p2) {
    pmin = p1;
    pmax = p2;
}

void Scene::aplicaTG(shared_ptr<TG> tg) {
    // TO DO
}

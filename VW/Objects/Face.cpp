#include "Face.hh"
#include <cmath>

Face::Face() {
}

Face::Face(int i1, int i2, int i3, int i4)
{
    idxVertices.push_back(i1);
    idxVertices.push_back(i2);
    idxVertices.push_back(i3);
    if (i4!=-1) idxVertices.push_back(i4);
}

// hit() de Triangle modificat per treballar amb indexos de vertexs i plans
bool Face::hit(const vector<vec3> &V, const vector<shared_ptr<Plane>> &P, Ray& raig, float tmin, float tmax) const {
    // Dades necessaries per computar
    shared_ptr<Plane> p = P.at(idxPlane);
    vec3 v1 = V.at(idxVertices.at(0));
    vec3 v2 = V.at(idxVertices.at(1));
    vec3 v3 = V.at(idxVertices.at(2));
    vec3 normal = p->getNormal();

    // Interseccio amb el pla del triangle?
    float t;
    if (!p->isIntersection(&t, raig.getOrigin(), raig.getDirection(), tmin, tmax)) {
        return false;
    }

    // Comprovacio interseccio dins el triangle (recorregut antihorari)
    vec3 point = raig.pointAt(t);

    // P a la dreta de l'aresta v1v2
    if (dot(normal, cross(v2 - v1, point - v1)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v2v3
    if (dot(normal, cross(v3 - v2, point - v2)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v3v1
    if (dot(normal, cross(v1 - v3, point - v3)) < 0) {
        return false;
    }

    // Interior del triangle, registrem el hit
    shared_ptr<HitRecord> info = make_shared<HitRecord>();
    info->t = t;
    info->p = point;

    // La normal a un triangle es la mateixa per tots els punts
    info->normal = normal;
    info->mat = p->getMaterial();
    raig.addHit(info);
    return true;
}

// hit() però usant insertHit() al raig
bool Face::allHits(const vector<vec3> &V, const vector<shared_ptr<Plane>> &P, Ray& raig, float tmin, float tmax) const {
    // Dades necessaries per computar
    shared_ptr<Plane> p = P.at(idxPlane);
    vec3 v1 = V.at(idxVertices.at(0));
    vec3 v2 = V.at(idxVertices.at(1));
    vec3 v3 = V.at(idxVertices.at(2));
    vec3 normal = p->getNormal();

    // Interseccio amb el pla del triangle?
    float t;
    if (!p->isIntersection(&t, raig.getOrigin(), raig.getDirection(), tmin, tmax)) {
        return false;
    }

    // Comprovacio interseccio dins el triangle (recorregut antihorari)
    vec3 point = raig.pointAt(t);

    // P a la dreta de l'aresta v1v2
    if (dot(normal, cross(v2 - v1, point - v1)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v2v3
    if (dot(normal, cross(v3 - v2, point - v2)) < 0) {
        return false;
    }

    // P a la dreta de l'aresta v3v1
    if (dot(normal, cross(v1 - v3, point - v3)) < 0) {
        return false;
    }

    // Interior del triangle, registrem el hit
    shared_ptr<HitRecord> info = make_shared<HitRecord>();
    info->t = t;
    info->p = point;

    // La normal a un triangle es la mateixa per tots els punts
    info->normal = normal;
    info->mat = p->getMaterial();
    raig.insertHit(info);
    return true;
}

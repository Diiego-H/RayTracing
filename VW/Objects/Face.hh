#pragma once

#include <vector>
#include "glm/glm.hpp"

#include "Plane.hh"

using namespace std;
using namespace glm;

typedef vec4 Vertices;
// Face - representa una cara d'un objecte 3D
class Face
{
public:
    Face();

    // constructor a partir de 3 o 4 indexs a vertex
    Face(int i1, int i2, int i3, int i4 = -1);

    // Interseccio de la cara
    bool hit(const vector<vec3> &V, const vector<shared_ptr<Plane>> &P, Ray &raig, float tmin, float tmax) const;
    bool allHits(const vector<vec3> &V, const vector<shared_ptr<Plane>> &P, Ray &raig, float tmin, float tmax) const;

    vector<int> idxVertices; // vector amb els indexs dels vertexs de la cara
    int idxPlane;            // index del pla corresponent a la cara
};

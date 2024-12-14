#pragma once

#include <vector>

#include <QString>
#include <QFile>
#include <QRegularExpression>

#include "Controller.hh"
#include "Object.hh"
#include "Face.hh"
#include "Triangle.hh"
#include "Box.hh"
#include "Sphere.hh"
#include "glm/gtc/random.hpp"

using namespace std;

class Mesh : public Object
{
public:
    Mesh() {};
    Mesh(const QString &fileName);

    virtual bool hit( Ray& r, float tmin, float tmax) const override;
    virtual bool allHits(Ray& r, float tmin, float tmax) const override;

    virtual void update(int nframe) override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    virtual ~Mesh();
private:

    QString nom;
    vector<shared_ptr<Face>> cares; // faces o cares de l'objecte
    vector<vec3> vertexs; // vertexs de l'objecte sense repetits
    vector<shared_ptr<Plane>> plans; // plans de la malla

    shared_ptr<Box> aabb; // axis aligned bounding box
    shared_ptr<Sphere> bSphere; // bounding sphere

    void load(QString filename);
    void makeTriangles();
    void makeBoundingVolumes();
    Sphere welzlMinimumSphere(vector<vec3> p, vector<vec3> boundary);
    Sphere TriangleCircumsphere(vec3 a, vec3 b, vec3 c);
    Sphere TetrahedronCircumsphere(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& v3);
};


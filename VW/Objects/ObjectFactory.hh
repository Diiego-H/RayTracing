#pragma once

#include "Object.hh"
#include "Sphere.hh"
#include "Plane.hh"
#include "Triangle.hh"
#include "Box.hh"
#include "Mesh.hh"
#include "FittedPlane.hh"
#include "EnvironmentalSphere.hh"

class ObjectFactory
{
    ObjectFactory(){};

public:
    typedef enum  {
        SPHERE,
        PLANE,
        BOX,
        TRIANGLE,
        MESH,
        FITTEDPLANE,
        ENVIRONMENTALSPHERE
    } OBJECT_TYPES;

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Object> createObject(OBJECT_TYPES t);

    // Crea un objecte de nom s
    shared_ptr<Object> createObject(  QString s,  OBJECT_TYPES t);

    OBJECT_TYPES getIndexType (shared_ptr<Object> l);
    OBJECT_TYPES getObjectType(QString name);
    QString      getNameType(int  t);
};


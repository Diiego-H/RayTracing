#pragma once

#include "VW/Objects/Object.hh"

class Scene: public Hittable, public Animable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           TEMPORALVW
    } DATA_TYPES;

    typedef enum
    {
        MATERIAL
    } MATERIAL_TYPES;


    QString name;

    // dimensions de l'escena virtual que es renderintza: capsa mínima contenidora
    vec3 pmin, pmax;

    // Vector d'objectes continguts a l'escena
    vector<shared_ptr<Object>> objects;


    Scene();
    virtual ~Scene() {};

    // TO DO Funcio que calcula la interseccio del raig r amb l'escena. Guarda la informacio
    // del punt d'interseccio més proper a t_min del Raig, punt que està entre t_min i t_max del Raig.
    // Retorna cert si existeix la interseccio, fals, en cas contrari
    virtual bool hit(Ray& raig, float tmin, float tmax) const override;

    // TO DO: Mètode que retorna totes les interseccions que es troben al llarg del raig
    virtual bool allHits(Ray& r, float tmin, float tmax) const override;

    void update(int nframe) override;

    void aplicaTG(shared_ptr<TG> tg) override;

    void setDimensions(vec3 p1, vec3 p2);

    void addObject (shared_ptr<Object> obj) { objects.push_back(obj);};

    void clear() { objects.clear();};

};


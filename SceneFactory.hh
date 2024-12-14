#pragma once

#include <QString>

#include "DataService/Serializable.hh"
#include "Scene.hh"


class SceneFactory: public Serializable
{
public:
    typedef enum
    {
           VIRTUALWORLD,
           TEMPORALVW
    } SCENE_TYPES;

    SceneFactory() {};
    virtual ~SceneFactory() {};

    virtual shared_ptr<Scene> createScene()=0;
    virtual shared_ptr<Scene> createScene(QString nomFitxer)=0;

    static SCENE_TYPES getSceneFactoryType( QString name);
    QString            getNameType(SCENE_TYPES t) const;

protected:
    shared_ptr<Scene> scene;
    SCENE_TYPES currentType;

};



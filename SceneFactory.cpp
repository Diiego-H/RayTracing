#include "SceneFactory.hh"


SceneFactory::SCENE_TYPES SceneFactory::getSceneFactoryType( QString name) {
    if (name=="VIRTUALWORLD") return SCENE_TYPES::VIRTUALWORLD;
    else if (name=="TEMPORALVW") return SCENE_TYPES::TEMPORALVW;
    else return  SCENE_TYPES::VIRTUALWORLD;
}

QString SceneFactory::getNameType(SCENE_TYPES t) const
{
    switch(t) {
    case VIRTUALWORLD:
        return(QString("VIRTUALWORLD"));
        break;
    case TEMPORALVW:
        return(QString("TEMPORALVW"));
        break;
    }
}

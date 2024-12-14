#include "ShadingFactory.hh"


shared_ptr<ShadingStrategy> ShadingFactory::createShading(SHADING_TYPES t) {
    shared_ptr<ShadingStrategy> s;
    switch(t) {
    case COLORSHADING:
        s= make_shared<ColorShading>();
        break;
    case NORMAL:
        s= make_shared<NormalShading>();
        break;
    case NCOLORSHADING:
        s= make_shared<NColorShading>();
        break;
    case BLINNPHONG:
        s = make_shared<BlinnPhongShading>();
        break;
    case AOSHADING:
        s = make_shared<AOShading>();
        break;
    case TOON:
        s = make_shared<CelShading>();
        break;
    case BLINNPHONGPENOMBRES:
        s = make_shared<BlinnPhongPenombresShading>();
        break;
    default:
        s = nullptr;
    }
    return s;
}

ShadingFactory::SHADING_TYPES ShadingFactory::getShadingType(QString name) {
    
    if (name=="COLORSHADING") return SHADING_TYPES::COLORSHADING;
    if (name=="NORMAL") return SHADING_TYPES::NORMAL;
    if (name=="NCOLORSHADING") return SHADING_TYPES::NCOLORSHADING;
    if (name=="BLINNPHONG") return SHADING_TYPES::BLINNPHONG;
    if (name=="TOON") return SHADING_TYPES::TOON;
    if (name=="AOSHADING") return SHADING_TYPES::AOSHADING;
    if (name=="BLINNPHONGPENOMBRES") return SHADING_TYPES::BLINNPHONGPENOMBRES;

    return SHADING_TYPES::COLORSHADING;
}

QString ShadingFactory::getNameType(SHADING_TYPES t) {
    switch (t) {
    case COLORSHADING:
        return (QString("COLORSHADING"));
        break;
    case NORMAL:
        return (QString("NORMAL"));
        break;
    case NCOLORSHADING:
        return (QString("NCOLORSHADING"));
        break;
    case BLINNPHONG:
        return (QString("BLINNPHONG"));
        break;
    case TOON:
        return (QString("TOON"));
        break;
    case AOSHADING:
        return (QString("AOSHADING"));
        break;
    case BLINNPHONGPENOMBRES:
        return (QString("BLINNPHONGPENOMBRES"));
        break;

    default:
        return(QString(""));
    }
}
ShadingFactory::SHADING_TYPES ShadingFactory::getIndexType(shared_ptr<ShadingStrategy> m) {
    if (dynamic_pointer_cast<ColorShading>(m) != nullptr) {
        return SHADING_TYPES::COLORSHADING;
    } else if (dynamic_pointer_cast<NormalShading>(m) != nullptr) {
        return SHADING_TYPES::NORMAL;
    } else if (dynamic_pointer_cast<NColorShading>(m) != nullptr) {
        return SHADING_TYPES::NCOLORSHADING;
    } else if (dynamic_pointer_cast<BlinnPhongShading>(m) != nullptr) {
        return SHADING_TYPES::BLINNPHONG;
    } else if (dynamic_pointer_cast<CelShading>(m) != nullptr) {
        return SHADING_TYPES::TOON;
    } else if (dynamic_pointer_cast<AOShading>(m) != nullptr) {
        return SHADING_TYPES::AOSHADING;
    } else if (dynamic_pointer_cast<BlinnPhongPenombresShading>(m) != nullptr) {
        return SHADING_TYPES::BLINNPHONGPENOMBRES;
    } else
        return SHADING_TYPES::COLORSHADING;
}

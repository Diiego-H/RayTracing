#include "Object.hh"

Object::Object()
{
    material = nullptr;
}

void Object::setMaterial(shared_ptr<Material> m)
{
    material = m;
}

shared_ptr<Material> Object::getMaterial()
{
    return material;
}

void Object::read(const QJsonObject &json)
{
    if (json.contains("material") && json["material"].isObject())
    {
        QJsonObject auxMat = json["material"].toObject();
        if (auxMat.contains("type") && auxMat["type"].isString())
        {
            QString tipus = auxMat["type"].toString().toUpper();
            MaterialFactory::MATERIAL_TYPES t = MaterialFactory::getInstance().getMaterialType(tipus);
            material = MaterialFactory::getInstance().createMaterial(t);
            material->read(auxMat);
        }
    }
    // llegim les animacions
    if (json.contains("animations") && json["animations"].isArray())
    {
        QJsonArray auxVec = json["animations"].toArray();
        for (int objectIndex = 0; objectIndex < auxVec.size(); objectIndex++)
        {
            QJsonObject auxObj = auxVec[objectIndex].toObject();
            double frameIni, frameFinal;
            if (auxObj.contains("frameIni") && auxObj["frameIni"].isDouble())
            {
                frameIni = auxObj["frameIni"].toDouble();
            }
            if (auxObj.contains("frameFinal") && auxObj["frameFinal"].isDouble())
            {
                frameFinal = auxObj["frameFinal"].toDouble();
            }
            if (auxObj.contains("translation") && auxObj["translation"].isArray())
            {
                QJsonArray trans = auxObj["translation"].toArray();
                vec3 translation;
                translation.x = trans[0].toDouble();
                translation.y = trans[1].toDouble();
                translation.z = trans[2].toDouble();

                shared_ptr<Animation> anim = make_shared<Animation>();
                anim->frameIni = frameIni;
                anim->frameFinal = frameFinal;
                anim->transf = make_shared<TranslateTG>(translation);
                this->addAnimation(anim);
            }
            if (auxObj.contains("scaling") && auxObj["scaling"].isArray())
            {
                QJsonArray scal_fac = auxObj["scaling"].toArray();
                vec3 scaling_factor;
                scaling_factor.x = scal_fac[0].toDouble();
                scaling_factor.y = scal_fac[1].toDouble();
                scaling_factor.z = scal_fac[2].toDouble();

                shared_ptr<Animation> anim = make_shared<Animation>();
                anim->frameIni = frameIni;
                anim->frameFinal = frameFinal;
                anim->transf = make_shared<ScaleTG>(scaling_factor);
                this->addAnimation(anim);
            }

            // TO DO: afegir lectura de rotacions
        }
    }

    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();
}

//! [1]
void Object::write(QJsonObject &json) const
{
    json["name"] = name;

    QJsonObject materialObject;
    auto value = MaterialFactory::getInstance().getIndexType(material);
    QString className = MaterialFactory::getInstance().getNameType(value);

    material->write(materialObject);
    materialObject["type"] = className;

    json["material"] = materialObject;
}
//! [1]

void Object::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Material:"
                        << "\n";
    auto value = MaterialFactory::getInstance().getIndexType(material);
    QString className = MaterialFactory::getInstance().getNameType(value);
    QTextStream(stdout) << indent << "type:\t" << className << "\n";
    material->print(indentation + 2);
}

#pragma once

#include <QFile>
#include "SceneFactory.hh"
#include "VW/Objects/ObjectFactory.hh"
#include "VW/Materials/Lambertian.hh"

class SceneFactoryVirtual : public SceneFactory
{

public:
    SceneFactoryVirtual();
    SceneFactoryVirtual(QString nomFitxer);

    virtual shared_ptr<Scene>  createScene (QString nomFitxer) override;
    virtual shared_ptr<Scene>  createScene() override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    bool load(QString nameFile);
    bool save(QString nameFile) const;

    void OneSphere(shared_ptr<Scene> s, vec3 position, float radius);
};



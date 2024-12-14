#include "Controller.hh"

Controller::Controller()
{
    scene = make_shared<Scene>();
    // Valors per defecte de visualSetup
    visualSetup = make_shared<SetUp>();
}


bool Controller::createScene(SceneFactory::SCENE_TYPES currentType, QString name) {
    shared_ptr<SceneFactory> sf = nullptr;
    switch (currentType)  {
    case SceneFactory::SCENE_TYPES::VIRTUALWORLD:
        sf = make_shared<SceneFactoryVirtual>(name);
        break;
    case SceneFactory::SCENE_TYPES::TEMPORALVW:
        // TO DO:  Afegir les factories de escenes temporals amb les animacions
        sf = make_shared<SceneFactoryTemporal>(name);
        break;
    default:
        break;
    }
    scene = sf->createScene(name);
    return (scene != nullptr);
}

bool Controller::createScene(vec3 position, float radius) {
    // Create a single Sphere
    auto sf = make_shared<SceneFactoryVirtual>();
    scene= make_shared<Scene>();
    sf->OneSphere(scene, position, radius);
    return true;

}
bool Controller::createScene() {
    //TODO: Pots usar la SceneFactoryVirtual
    // per a fer una escena amb multiples esferes
    //auto sf = make_shared<SceneFactoryVirtual>();
    //scene = sf->createScene();

    auto sf = make_shared<SceneFactoryTemporal>();
    scene = sf->createScene();
    return true;
}

bool Controller::createScene(int nFrames) {

    //TO DO Fase 3 opcional: Codi exemple amb animacions però que es pot canviar
    // pel que creguis convenient

    scene= make_shared<Scene>();

    auto sphere = make_shared<Sphere>(vec3(0, 0, -1), 0.5);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));

    shared_ptr<Animation> anim = make_shared<Animation>();
    anim->transf =  make_shared<TranslateTG>(vec3(0.2));
    sphere->addAnimation(anim);

    scene->objects.push_back(sphere);
    return true;
}
bool Controller::createSettings(QString name) {
    // Create Settings and set them to the scene
    visualSetup = make_shared<SetUp>();
    if (visualSetup->load(name) ) {
        visualSetup->print(0);
        return (true);
    }
    return false;
}

void Controller::rendering(QImage *image) {
    RayTracing *tracer = new RayTracing(image);
    tracer->play();
    delete tracer;
}


bool Controller::createShading(ShadingFactory::SHADING_TYPES t) {
    visualSetup->setShadingStrategy(ShadingFactory::getInstance().createShading(t));
    return visualSetup->getShadingStrategy()!=nullptr;

}

void Controller::update(int i) {
    scene->update(i);
}

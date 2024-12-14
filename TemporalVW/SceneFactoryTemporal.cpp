#include "SceneFactoryTemporal.hh"


SceneFactoryTemporal::SceneFactoryTemporal():SceneFactory()
{

}

SceneFactoryTemporal::SceneFactoryTemporal(QString filename) {
    createScene(filename);
}

shared_ptr<Scene> SceneFactoryTemporal::createScene() {
    scene= make_shared<Scene>();
    // Pots posar el codi aqui per generar una escena de forma procedimental

    // escena refeta pel Tutorial 3 - Homework 1

    auto box = make_shared<Box>(vec3(-100.0f, -2.0f, -100.0f), vec3(100.0f, -1.0f, 100.0f)); 
    auto silver = make_shared<Metal>(
        vec3(0.19225, 0.19225, 0.19225),
        vec3(0.50754,0.50754,0.50754),
        vec3(0.708273,0.708273,0.708273),
        10.0f
    );
    box->setMaterial(silver);
    scene->objects.push_back(box);

    // esfera de plastic
    auto plastic_sphere = make_shared<Sphere>(vec3(-0.5f,-0.5f,-0.5f), 0.5f);
    auto plastic = make_shared<Lambertian>(
        vec3(0.0f,0.1f,0.06f),
        vec3(0.0f,0.50980392f,0.50980392f),
        vec3(0.50196078f,0.50196078f,0.50196078f),
        0.25f
    );
    plastic_sphere->setMaterial(plastic);
    scene->objects.push_back(plastic_sphere);

    // esfera d'or
    auto gold_sphere = make_shared<Sphere>(vec3(0.5f,-0.5f,-0.5f), 0.5f);
    auto gold = make_shared<Lambertian>(
        vec3(0.24f,0.1995f,0.0745f),
        vec3(0.8f,0.60648f,0.22648f),
        vec3(0.628281f,0.555802f,0.366065f),
        10.0f
    );
    gold_sphere->setMaterial(gold);
    scene->objects.push_back(gold_sphere);

    // esfera transparent
    auto trans_sphere = make_shared<Sphere>(vec3(0.0f,-0.5f,0.5f), 0.5f);
    auto trans = make_shared<Transparent>(
        vec3(0.2f,0.2f,0.2f),
        vec3(0.6f,0.6f,0.6f),
        vec3(0.7f,0.7f,0.7f),
        12.0f
    );
    trans->Kt = vec3(0.9f,0.9f,0.9f);
    trans->opacity = 0.1f;
    trans->nut = 1.4f;
    trans->dmax = 2.0f;
    trans_sphere->setMaterial(trans);
    scene->objects.push_back(trans_sphere);


    // spheres animades
    int n_instants = 30;
    int path_instants = n_instants / 3;
    Controller::getInstance()->setMaxFrames(n_instants);

    #define OFFSET 0.25f
    #define OFFSET2 0.176767f
    float s_radius = 0.15f;


    vec3 p1 = vec3(0.0f, 0.5f, 1.0f + OFFSET);
    vec3 p2 = vec3(-1.0f-OFFSET2, 0.5f, -1.0f-OFFSET2);
    vec3 p3 = vec3(1.0f+OFFSET2, 0.5f, -1.0f-OFFSET2);

    // esfera de plastic vermell
    auto ss1 = make_shared<Sphere>(p1, s_radius);
    auto ss1_mat = make_shared<Lambertian>(
        vec3(0.2f,0.1f,0.1f),
        vec3(0.5f,0.0f,0.0f),
        vec3(0.7f,0.6f,0.5f),
        0.25f
    );
    ss1->setMaterial(ss1_mat);
    shared_ptr<Animation> anim1 = make_shared<Animation>();
    anim1->frameIni = 0;
    anim1->frameFinal = 10;
    vec3 translation1 = (1.0f/path_instants)*(p2-p1);
    anim1->transf = make_shared<TranslateTG>(translation1);
    ss1->addAnimation(anim1);

    shared_ptr<Animation> anim2 = make_shared<Animation>();
    anim2->frameIni = 11;
    anim2->frameFinal = 20;
    vec3 translation2 = (1.0f/path_instants)*(p3-p2);
    anim2->transf = make_shared<TranslateTG>(translation2);
    ss1->addAnimation(anim2);

    shared_ptr<Animation> anim3 = make_shared<Animation>();
    anim3->frameIni = 21;
    anim3->frameFinal = 30;
    vec3 translation3 = (1.0f/path_instants)*(p1-p3);
    anim3->transf = make_shared<TranslateTG>(translation3);
    ss1->addAnimation(anim3);
    

    // esfera de plastic
    auto ss2 = make_shared<Sphere>(p2, s_radius);
    auto ss2_mat = make_shared<Lambertian>(
        vec3(0.05375f,0.05f,0.06625f),
        vec3(0.18275f,0.17f,0.22525f),
        vec3(0.332741f,0.328634f,0.346435f),
        0.3f
    );
    ss2->setMaterial(ss2_mat);
    shared_ptr<Animation> anim1s2 = make_shared<Animation>();
    anim1s2->frameIni = 21;
    anim1s2->frameFinal = 30;
    anim1s2->transf = make_shared<TranslateTG>(translation1);
    ss2->addAnimation(anim1s2);

    shared_ptr<Animation> anim2s2 = make_shared<Animation>();
    anim2s2->frameIni = 0;
    anim2s2->frameFinal = 10;
    anim2s2->transf = make_shared<TranslateTG>(translation2);
    ss2->addAnimation(anim2s2);

    shared_ptr<Animation> anim3s2 = make_shared<Animation>();
    anim3s2->frameIni = 11;
    anim3s2->frameFinal = 20;
    anim3s2->transf = make_shared<TranslateTG>(translation3);
    ss2->addAnimation(anim3s2);

    // esfera de goma negra
    auto ss3 = make_shared<Sphere>(p3, s_radius);
    auto ss3_mat = make_shared<Lambertian>(
        vec3(0.02f,0.02f,0.02f),
        vec3(0.1f,0.1f,0.1f),
        vec3(0.4f,0.4f,0.4f),
        0.08f
    );
    ss3->setMaterial(ss3_mat);
    shared_ptr<Animation> anim1s3 = make_shared<Animation>();
    anim1s3->frameIni = 11;
    anim1s3->frameFinal = 20;
    anim1s3->transf = make_shared<TranslateTG>(translation1);
    ss3->addAnimation(anim1s3);

    shared_ptr<Animation> anim2s3 = make_shared<Animation>();
    anim2s3->frameIni = 21;
    anim2s3->frameFinal = 30;
    anim2s3->transf = make_shared<TranslateTG>(translation2);
    ss3->addAnimation(anim2s3);

    shared_ptr<Animation> anim3s3 = make_shared<Animation>();
    anim3s3->frameIni = 0;
    anim3s3->frameFinal = 10;
    anim3s3->transf = make_shared<TranslateTG>(translation3);
    ss3->addAnimation(anim3s3);
  

    scene->objects.push_back(ss1);
    scene->objects.push_back(ss2);
    scene->objects.push_back(ss3);


    vec3 min_box_r = vec3(3.0f,-2.0f, -3.0f);
    vec3 max_box_r = vec3(4.0f, -1.0f, -2.0f);
    vec3 box_up = vec3(0.0f, 1.0f, 0.0f);

    auto box_r = make_shared<Box>(min_box_r, max_box_r); 
    auto box_r_mat = make_shared<Lambertian>(
        vec3(0.01, 0.01, 0.01),
        vec3(0.01,0.01,0.01),
        vec3(0.01,0.01,0.01),
        1.0f
    );
    box_r->setMaterial(box_r_mat);

    shared_ptr<Animation> box_r_up = make_shared<Animation>();
    box_r_up->frameIni = 0;
    box_r_up->frameFinal = 15;
    box_r_up->transf = make_shared<TranslateTG>((1.0f/15.0f)*box_up);
    box_r->addAnimation(box_r_up);

    shared_ptr<Animation> box_r_down = make_shared<Animation>();
    box_r_down->frameIni = 15;
    box_r_down->frameFinal = 30;
    box_r_down->transf = make_shared<TranslateTG>((1.0f/15.0f)*-box_up);
    box_r->addAnimation(box_r_down);

    scene->objects.push_back(box_r);

    float spheres_scale_factor = 1.1f;
    float inv_s_s_factor = 1.0f/spheres_scale_factor;
    float side_spheres_radius = 0.2f;

    auto ssr = make_shared<Sphere>(
        (1.0f/2.0f)*(max_box_r+min_box_r+vec3(0.0f,3.0f,0.0f)),
        side_spheres_radius);
    auto ssr_mat = make_shared<Metal>(
        vec3(0.05375f,0.05f,0.06625f),
        vec3(0.18275f,0.17f,0.22525f),
        vec3(0.332741f,0.328634f,0.346435f),
        12.0f
    );
    ssr->setMaterial(ssr_mat);
    shared_ptr<Animation> ssr_scale_up = make_shared<Animation>();
    ssr_scale_up->frameIni = 0;
    ssr_scale_up->frameFinal = 15;
    ssr_scale_up->transf = make_shared<ScaleTG>(vec3(spheres_scale_factor, spheres_scale_factor, spheres_scale_factor));
    ssr->addAnimation(ssr_scale_up);
    shared_ptr<Animation> ssr_scale_down = make_shared<Animation>();
    ssr_scale_down->frameIni = 15;
    ssr_scale_down->frameFinal = 30;
    ssr_scale_down->transf = make_shared<ScaleTG>(vec3(inv_s_s_factor, inv_s_s_factor, inv_s_s_factor));
    ssr->addAnimation(ssr_scale_down);

    scene->objects.push_back(ssr);


    vec3 min_box_l = vec3(-4.0f,-2.0f, -3.0f);
    vec3 max_box_l = vec3(-3.0f, -1.0f, -2.0f);

    auto box_l = make_shared<Box>(min_box_l, max_box_l); 
    auto box_l_mat = make_shared<Lambertian>(
        vec3(0.01, 0.01, 0.01),
        vec3(0.01,0.01,0.01),
        vec3(0.01,0.01,0.01),
        1.0f
    );
    box_l->setMaterial(box_l_mat);

    shared_ptr<Animation> box_l_up = make_shared<Animation>();
    box_l_up->frameIni = 0;
    box_l_up->frameFinal = 15;
    box_l_up->transf = make_shared<TranslateTG>((1.0f/15.0f)*box_up);
    box_l->addAnimation(box_l_up);

    shared_ptr<Animation> box_l_down = make_shared<Animation>();
    box_l_down->frameIni = 15;
    box_l_down->frameFinal = 30;
    box_l_down->transf = make_shared<TranslateTG>((1.0f/15.0f)*-box_up);
    box_l->addAnimation(box_l_down);

    scene->objects.push_back(box_l);
    auto ssl = make_shared<Sphere>(
        (1.0f/2.0f)*(max_box_l+min_box_l+vec3(0.0f,3.0f,0.0f)),
        side_spheres_radius);
    auto ssl_mat = make_shared<Metal>(
        vec3(0.0215,0.1745,0.0215),
        vec3(0.07568,0.61424, 0.07568),
        vec3(0.633,0.727811,0.633),
        0.6f
    );
    ssl->setMaterial(ssl_mat);
    shared_ptr<Animation> ssl_scale_up = make_shared<Animation>();
    ssl_scale_up->frameIni = 0;
    ssl_scale_up->frameFinal = 15;
    ssl_scale_up->transf = make_shared<ScaleTG>(vec3(spheres_scale_factor, spheres_scale_factor, spheres_scale_factor));
    ssl->addAnimation(ssl_scale_up);
    shared_ptr<Animation> ssl_scale_down = make_shared<Animation>();
    ssl_scale_down->frameIni = 15;
    ssl_scale_down->frameFinal = 30;
    ssl_scale_down->transf = make_shared<ScaleTG>(vec3(inv_s_s_factor, inv_s_s_factor, inv_s_s_factor));
    ssl->addAnimation(ssl_scale_down);

    scene->objects.push_back(ssl);





    // -----  SETUP -----
    auto setup = make_shared<SetUp>();

    // camera
    vec3 lookfrom = vec3(0.0f,2.0f,3.0f);
    vec3 lookat = vec3(0.0f,0.0f,0.0f);
    vec3 vup = vec3(0.0f,1.0f,0.0f);
    double vfov = 60.0f;
    double aspect_ratio = 1.77f;
    double pixelsX = 600;
    double aperture = 100.0f; // no usat
    double defocus_blur = false;
    auto camera = make_shared<Camera>( lookfrom,
                lookat,
                vup,
                vfov, // vertical field-of-view in degrees
                aspect_ratio, pixelsX, aperture, defocus_blur);

    setup->setCamera(camera);

    // lights
    vector<shared_ptr<Light>> lights;

    vec3 posicio = vec3(-2.0f, 4.0f, 8.0f);
    vec3 Ia = vec3(0.35f,0.3f,0.3f);
    vec3 Id = vec3(0.75f,0.7f,0.7f);
    vec3 Is = vec3(1.0f,0.9f,0.9f);
    double a = 0.5;
    double b = 0.0;
    double c = 0.01;
    double radius = 1.0f;

    // area light
    /*
    lights.push_back(make_shared<AreaLight>(
        posicio, Ia,Id,Is, a, b, c, radius
    ));
    */
    lights.push_back(make_shared<PointLight>(
        posicio, Ia, Id, Is, a, b, c
    ));

    setup->setLights(lights);

    setup->setGlobalLight(vec3(0.1f,0.1f,0.1f));

    setup->setBackground(true);
    setup->setTopBackground(vec3(0.5f, 0.7f, 1.0f));
    setup->setDownBackground(vec3(1.0f, 1.0f, 1.0f));

    int maxDepth = 4;//4;
    int numSamples = 10;//10;
    setup->setMAXDEPTH(maxDepth);
    setup->setSamples(numSamples);

    auto shade = ShadingFactory::getInstance().createShading(ShadingFactory::BLINNPHONG);
    setup->setShadingStrategy(shade);

    bool shadows = true;
    bool nhits = false;
    bool softShadows = true;
    bool bboxes = false;
    setup->setShadows(shadows);
    setup->setNHits(nhits);
    setup->setSoftShadows(softShadows);
    setup->setBoundingVolumes(false);



    Controller::getInstance()->setSetUp(setup);


    return scene;
}

shared_ptr<Scene> SceneFactoryTemporal::createScene(QString filename) {

    scene= make_shared<Scene>();
    load(filename);
    print(0);

    return scene;
}


void SceneFactoryTemporal::OneSphere(shared_ptr<Scene> s, vec3 position, float radius) {
    auto sphere = make_shared<Sphere>(position, radius);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));
    s->objects.push_back(sphere);

}

//! [3]
bool SceneFactoryTemporal::load(QString nameFile)
{
    QFile loadFile(nameFile);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the virtual scene file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData, &error));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json virtual scene file.");
        return false;
    }
    QJsonObject object = loadDoc.object();
    read(object);

    QTextStream(stdout) << "Loaded virtual scene using " << "...\n";
    return true;
}
//! [3]

//! [4]
bool SceneFactoryTemporal::save(QString nameFile) const
{
    QFile saveFile(QString(nameFile.append(".json")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open virtual scene file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(QJsonDocument(setUpObject).toJson());

    return true;
}

//! [0]
void SceneFactoryTemporal::read(const QJsonObject &json)
{
    if (json.contains("scene") && json["scene"].isString())
        scene->name = json["scene"].toString();
    if (json.contains("typeScene") && json["typeScene"].isString())
        currentType = getSceneFactoryType(json["typeScene"].toString());
    if (json.contains("numInstants") && json["numInstants"].isDouble())
        Controller::getInstance()->setMaxFrames(json["numInstants"].toDouble());


    if (json.contains("objects") && json["objects"].isArray()) {
        QJsonArray objectsArray = json["objects"].toArray();

        for (int objectIndex = 0; objectIndex < objectsArray.size(); objectIndex++) {
            QJsonObject objectObject = objectsArray[objectIndex].toObject();
            shared_ptr<Object> o;
            if (objectObject.contains("type") && objectObject["type"].isString()) {
                QString objStr = objectObject["type"].toString().toUpper();
                o = ObjectFactory::getInstance().createObject(ObjectFactory::getInstance().getObjectType(objStr));
                o->read(objectObject);
                scene->objects.push_back(o);
            }
        }
    }

}
//! [0]

void SceneFactoryTemporal:: write(QJsonObject &json) const
{
   json["scene"] = scene->name;
   json["typeScene"] = SceneFactory::getNameType(currentType);


    QJsonArray objectsArray;
    for (const shared_ptr<Object> &o : scene->objects) {
        QJsonObject objectObject;
        int  value = ObjectFactory::getInstance().getIndexType (o);
        QString className = ObjectFactory::getInstance().getNameType(value);

        o->write(objectObject);
        objectObject["type"] = className;
        objectsArray.append(objectObject);
    }
    json["objects"] = objectsArray;
}

void SceneFactoryTemporal::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "scene:\t" << scene->name << "\n";
    QTextStream(stdout) << indent << "typeScene:\t" << getNameType(currentType) << "\n";

    QTextStream(stdout) << indent << "Objects:\t\n";
    for (unsigned int i =0; i< scene->objects.size(); i++) {
        auto value = ObjectFactory::getInstance().getIndexType (scene->objects[i]);
        QString className = ObjectFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "name:\t" << scene->objects[i]->name <<"\n";
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";
        scene->objects[i]->print(2);
    }
 }

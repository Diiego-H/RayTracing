#pragma once

#include <QString>

#include "SceneFactory.hh"
#include "Render/ShadingFactory.hh"
#include "DataService/SetUp.hh"

// Tots els seguents includes estan usats al cpp de Controller.cpp
#include "VW/SceneFactoryVirtual.hh"
#include "TemporalVW/SceneFactoryTemporal.hh"
#include "VW/Materials/Lambertian.hh"
#include "VW/Objects/Sphere.hh"
#include "VW/TG/TranslateTG.hh"
#include "Render/RayTracing.hh"



using namespace std;

class Controller
{
private:
    shared_ptr<Scene>  scene;
    shared_ptr<SetUp>  visualSetup;
    int maxFrames = -1;

    static Controller* // Singleton

    // static pointer which will points to the instance of this class
    instancePtr;

    // Default constructor
    Controller();

public:

    // deleting copy constructor
    Controller(const Controller& obj)
        = delete;

    static Controller* getInstance() {
        // If there is no instance of class
        // then we can create an instance.
        if (instancePtr == NULL) {
          // We can access private members
          // within the class.
          instancePtr = new Controller();

          // returning the instance pointer
          return instancePtr;
        } else {
          // if instancePtr != NULL that means
          // the class already have an instance.
          // So, we are returning that instance
          // and not creating new one.
          return instancePtr;
        }
      }


    shared_ptr<Scene>  getScene() {return scene; }
    shared_ptr<SetUp>  getSetUp() {return visualSetup; }

    void setScene (shared_ptr<Scene> s) {  scene = s;}
    void setSetUp (shared_ptr<SetUp> v) {  visualSetup = v;}

    bool createScene(SceneFactory::SCENE_TYPES currentType, QString name);
    bool createScene(vec3 position, float radius);
    bool createScene();
    bool createScene(int nFrames);

    bool createSettings(QString name);
    bool createShading(ShadingFactory::SHADING_TYPES t);

    void rendering(QImage *image);
    void update(int i);
    void setMaxFrames(int i) {maxFrames = i;}
    int getMaxFrames() {return maxFrames;}
};

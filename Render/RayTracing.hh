
#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <QImage>

#include "Controller.hh"
#include "../DataService/SetUp.hh"

#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"

using namespace std;
using namespace glm;

class RayTracing {

	public:
        // Imatge on es calcularà el rendering
        QImage *image;

        // settings de l'algorisme de visualització: conté la camera, les llums, el
        // tipus de shadings, etc...
        shared_ptr<SetUp> setup;

        // Escena virtual
        shared_ptr<Scene>  scene;

        RayTracing(QImage *i);
        void setPixel(int x, int y, vec3 color);

        void play();

private:
        shared_ptr<ShadingStrategy> NColorShading;
        
        // Funció d'inicialització del raytracing.
        void init();

        // Funcio recursiva que calcula el color d'un pixel. Inicialment
        // es crida a cada pixel de forma no recursiva.
        vec3 getColorPixel (Ray &ray, int depth=0);
};


#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

class TG
{
public:
    glm::mat4 matTG;
    TG();
    ~TG();
    virtual glm::mat4 getTG();
};



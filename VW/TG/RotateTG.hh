#pragma once

#include "TG.hh"

class RotateTG : public TG
{
public:
    float angle;
    glm::vec3 rotation_axis;
    RotateTG(float angle, glm::vec3 rotation_axis);
};


#include "RotateTG.hh"

RotateTG::RotateTG(float angle, glm::vec3 rotation_axis)
{
    this->angle = angle;
    this->rotation_axis = rotation_axis;
    matTG = rotate(glm::mat4(1.0f), angle, rotation_axis);
}

#include "ScaleTG.hh"

ScaleTG::ScaleTG(glm::vec3 scaling_factor)
{
    matTG = scale(glm::mat4(1.0f), scaling_factor);
}

#pragma once

#include "TG.hh"

class ScaleTG : public TG
{
public:
    glm::vec3 scaling_factor;
    ScaleTG(glm::vec3 scaling_factor);
};


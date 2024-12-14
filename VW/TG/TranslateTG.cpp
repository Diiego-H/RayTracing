#include "TranslateTG.hh"

TranslateTG::TranslateTG(glm::vec3 trasl): traslation(trasl)
{
    matTG = translate(glm::mat4(1.0f), traslation);
}

TranslateTG::~TranslateTG()
{

}

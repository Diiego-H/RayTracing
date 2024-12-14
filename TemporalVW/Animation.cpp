#include "Animation.hh"

void Animable::addAnimation(shared_ptr<Animation> anim)
{
    animFrames.push_back(anim);
}

void Animable::update(int nframe)
{
    // No entenc que fa aquest codi que he comentat, crec que esta malament
    // bool trobat = false;
    // int i;
    // for (i = 0; i < animFrames[animFrames.size() - 1]->frameFinal && !trobat; i++)
    //     trobat = animFrames[i]->frameFinal >= nframe;

    // aplicaTG(animFrames[i - 1]->transf);

    // Iterem per les animacions, i si nframe esta entre el frame inicial i el final, apliquem la transformacio
    for (shared_ptr<Animation> animation: animFrames) {
        if (animation->frameIni <= nframe && nframe <= animation->frameFinal) {
            aplicaTG(animation->transf);
        }
    }
}

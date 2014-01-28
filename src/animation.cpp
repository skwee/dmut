#include "animation.h"

unsigned int Animation::sNext = 0;

Animation::Animation()
{
    mName = QString("Animation_%1").arg(sNext++);
}

#include "animation.h"

unsigned int Animation::Namer::sIndex = 0;

QString Animation::Namer::generate() {
    return QString("Animation %1").arg(sIndex++);
}

Animation::Animation() :
    Block(Namer::generate(), Block::Type::Animation), mFramesPerSecond(DEFAULT_FPS)
{
}

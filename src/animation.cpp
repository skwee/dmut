#include "animation.h"

unsigned int Animation::Namer::sIndex = 0;

QString Animation::Namer::generate() {
    return QString("Animation %1").arg(sIndex++);
}

Animation::Animation(Item* parent) :
    Item(Namer::generate(), parent, Item::CanHaveChildren, Item::ItemType::Animation), mFramesPerSecond(DEFAULT_FPS)
{
}

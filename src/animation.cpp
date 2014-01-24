#include "animation.h"

Animation::Animation(const QString& name) {
    setName(name);
}

void Animation::setName(const QString &name) {
    mName = name;
    setText(mName);
}

#include "animation.h"
#include "frame.h"
#include "namer.h"

Animation::Animation() :
    Item(Namer::generateAnimationName()), mFps(DEFAULT_FPS), mWrapMode(WrapMode::Once)
{}

int Animation::columnCount() const {
    return Item::columnCount() + 2; //fps + wrapmode
}

Qt::ItemFlags Animation::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Animation::getNewChild() {
    return new Frame();
}

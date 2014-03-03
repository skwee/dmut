#include "animation.h"
#include "frame.h"
#include "namer.h"

Animation::Animation() :
    Item(Namer::generateAnimationName()), mFps(DEFAULT_FPS), mWrapMode(WrapOnce)
{}

Qt::ItemFlags Animation::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Animation::getNewChild() {
    return new Frame();
}

QVariant Animation::data(int column, int role) const {
    if((role == Qt::EditRole) || (role == Qt::DisplayRole)) {
        if(column == 1) {
            return mFps;
        } else if (column == 2) {
            return static_cast<char>(mWrapMode);
        }
    }
    return Item::data(column, role);
}

bool Animation::setData(const QVariant &value, int column, int role) {
    if(role == Qt::EditRole) {
        if(column == 1) {
            mFps = static_cast<FramesPerSecond>(value.toInt());
            return true;
        } else if(column == 2) {
            mWrapMode = static_cast<WrapMode>(value.toInt());
            return true;
        }
    }
    return Item::setData(value, column, role);
}

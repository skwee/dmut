#include "animation.h"
#include "frame.h"
#include "namer.h"

#include <QPixmap>
#include <QPixmapCache>

Animation::Animation() :
    Item(Namer::generateAnimationName()), mWrapMode(WrapOnce), mLength(0.0f)
{}

Qt::ItemFlags Animation::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Animation::getNewChild() {
    return new Frame();
}

double Animation::fps() const {
    int totalFrames = 0;
    for(Item* frame: children()) {
        totalFrames += static_cast<Frame*>(frame)->getHold();
    }

    if(mLength == 0.0) return 0;
    return static_cast<double>(totalFrames) / mLength;
}

QVariant Animation::data(int column, int role) const {
    if((role == Qt::EditRole) || (role == Qt::DisplayRole)) {
        if(column == Item::ColumnAnimationFps) {
            return fps();
        } else if (column == Item::ColumnAnimationWrapMode) {
            return static_cast<char>(mWrapMode);
        } else if (column == Item::ColumnAnimationLength) {
            return length();
        }
    } else if ((role == Qt::DecorationRole)) {
        QString file;
        if(mWrapMode == WrapOnce) {
            file = ":/icons/wrapmode_once.png";
        } else {
            file = ":/icons/wrapmode_loop.png";
        }

        QPixmap pixmap;
        if(!QPixmapCache::find(file, &pixmap)) {
            pixmap.load(file);
            QPixmapCache::insert(file, pixmap);
        }

        return pixmap;
    }
    return Item::data(column, role);
}

bool Animation::setData(const QVariant &value, int column, int role) {
    if(role == Qt::EditRole) {
        if(column == Item::ColumnAnimationWrapMode) {
            mWrapMode = static_cast<WrapMode>(value.toInt());
            return true;
        } else if(column == Item::ColumnAnimationLength) {
            mLength = value.toDouble();
            return true;
        }
    }
    return Item::setData(value, column, role);
}

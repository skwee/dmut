#include "animation.h"
#include "frame.h"
#include "namer.h"

#include <QPixmap>
#include <QPixmapCache>

Animation::Animation() :
    Item(Namer::generateAnimationName()), mWrapMode(WrapOnce)
{}

Qt::ItemFlags Animation::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Animation::getNewChild() {
    return new Frame();
}

QVariant Animation::data(int column, int role) const {
    if((role == Qt::EditRole) || (role == Qt::DisplayRole)) {
        if(column == Item::ColumnAnimationFps) {
            double len = 0;
            for(Item* f: children()) {
                len += static_cast<Frame*>(f)->getDuration();
            }

            if(len == 0) return 0;
            return static_cast<double>(children().length()) / static_cast<double>(len);
        } else if (column == Item::ColumnAnimationWrapMode) {
            return static_cast<char>(mWrapMode);
        } else if (column == Item::ColumnAnimationLength) {
            double len = 0;
            for(Item* f: children()) {
                len += static_cast<Frame*>(f)->getDuration();
            }
            return len;
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
        }
    }
    return Item::setData(value, column, role);
}

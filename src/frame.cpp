#include "frame.h"
#include "namer.h"

#include <QPixmap>
#include <QPixmapCache>

Frame::Frame() :
    Item(Namer::generateFrameName()), mDuration(1), mSprite(nullptr)
{}

Qt::ItemFlags Frame::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Frame::getNewChild() {
    return nullptr;
}

QVariant Frame::data(int column, int role) const {
    if((role == Qt::EditRole) || (role == Qt::DisplayRole)) {
        if(column == Item::ColumnFrameDuration) {
            return mDuration;
        } else if(column == Item::ColumnFrameSpriteIcon) {
            return QVariant::fromValue<Sprite*>(mSprite);
        }
    } else if(role == Qt::DecorationRole) {
        QPixmap pixmap;
        if(mSprite == nullptr) {
            QString file = ":/icons/exclamation.png";
            if(!QPixmapCache::find(file, &pixmap)) {
                pixmap.load(file);
                QPixmapCache::insert(file, pixmap);
            }
        } else {
            if(!QPixmapCache::find(mSprite->uuid().toString(), &pixmap)) {
                pixmap = mSprite->pixmap().copy().scaled(QSize(16, 16));
                QPixmapCache::insert(mSprite->uuid().toString(), pixmap);
            }
        }
        return pixmap;
    }
    return Item::data(column, role);
}

bool Frame::setData(const QVariant &value, int column, int role) {
    if(role == Qt::EditRole) {
        if(column == Item::ColumnFrameDuration) {
            mDuration = static_cast<Duration>(value.toDouble());
            return true;
        } else if(column == Item::ColumnFrameSprite) {
            mSprite = value.value<Sprite*>();
            return true;
        }
    }
    return Item::setData(value, column, role);
}

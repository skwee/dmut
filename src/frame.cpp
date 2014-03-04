#include "frame.h"
#include "namer.h"

#include <QPixmap>
#include <QPixmapCache>

Frame::Frame() :
    Item(Namer::generateFrameName()), mDuration(1)
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
        }
    } else if(role == Qt::DecorationRole) {
        //@TODO if no sprite selected
        QString file = ":/icons/exclamation.png";
        QPixmap pixmap;
        if(!QPixmapCache::find(file, &pixmap)) {
            pixmap.load(file);
            QPixmapCache::insert(file, pixmap);
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
        }
    }
    return Item::setData(value, column, role);
}

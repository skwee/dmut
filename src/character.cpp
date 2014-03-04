#include "character.h"
#include "animation.h"
#include "namer.h"

#include <QPixmap>
#include <QPixmapCache>

Character::Character(const QString &name) :
    Item(name)
{}

Qt::ItemFlags Character::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Character::getNewChild() {
    return new Animation();
}

QVariant Character::data(int column, int role) const {
    if(role == Qt::DecorationRole) {
        QString file = ":/icons/stickman.png";
        QPixmap pixmap;
        if(!QPixmapCache::find(file, &pixmap)) {
            pixmap.load(file);
            QPixmapCache::insert(file, pixmap);
        }
        return pixmap;
    }
    return Item::data(column, role);
}

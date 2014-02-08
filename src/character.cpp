#include "character.h"
#include "animation.h"
#include "namer.h"

Character::Character(const QString &name) :
    Item(name)
{}

int Character::columnCount() const {
    return Item::columnCount();
}

Qt::ItemFlags Character::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Character::getNewChild() {
    return new Animation();
}

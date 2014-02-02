#include "item.h"

Item::Item(Block::ptr block, Item *parent) :
    mBlock(block), mParent(parent)
{}

Item::~Item() {
    qDeleteAll(mChildren);
}

void Item::add(Item *item) {
    item->mParent = this;
    mChildren.push_back(item);
}

Item* Item::at(int index) const {
    if(indexIsValid(index)) return mChildren.at(index);
    return nullptr;
}

void Item::remove(int index) {
    if(indexIsValid((index)))
        delete mChildren.takeAt(index);
}

void Item::removeAll() {
    qDeleteAll(mChildren);
    mChildren.clear();
}

void Item::removeSelf() {
    if(mParent)
        mParent->mChildren.removeOne(this);
}

int Item::indexOfSelf() {
    if(mParent)
        return mParent->mChildren.indexOf(this);
    return -1;
}

bool Item::contains(Block::ptr block) {
    for(Item* i : mChildren) {
        if(i->block() == block) return true;
    }
    return false;
}

bool Item::swapItems(int oldIndex, int newIndex) {
    if((oldIndex < 0) || (oldIndex >= mChildren.size())) return false;
    if((newIndex < 0) || (newIndex >= mChildren.size())) return false;

    mChildren.swap(oldIndex, newIndex);
    return true;
}

QString Item::name() const {
    if(mBlock) return mBlock->name();
    return QString("UnNamedBlock");
}

Item::RenameResult Item::rename(const QString &name) {
    if(!mBlock) return Item::RenameResult::NotValid;

    if(name.isEmpty())
        return Item::RenameResult::Empty;

    if(name.length() > MAX_NAME_LENGTH)
        return Item::RenameResult::TooLong;

    if((mParent) && (!mParent->isNameUniqueAmongSiblings(name, this)))
        return Item::RenameResult::Duplicate;

    mBlock->rename(name);
    return Item::RenameResult::Ok;
}

QVariant Item::display() const {
    if(mBlock) return mBlock->display();
    return QVariant();
}

QVariant Item::decoration() const {
    if(mBlock) return mBlock->decoration();
    return QVariant();
}

int Item::row() {
    if(mParent) return mParent->mChildren.indexOf(this);
    return 0;
}

bool Item::indexIsValid(int index) const {
    return ((index >= 0) && (index < mChildren.size()));
}

bool Item::isNameUniqueAmongSiblings(const QString &name, const Item *except) {
    for(const Item* i : mChildren) {
        if(i == except) continue;
        if(i->mBlock->name().compare(name) == 0) return false;
    }

    return true;
}

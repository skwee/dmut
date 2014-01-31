#include "item.h"

const char* ItemOptionsMismatchException::what() const noexcept {
    return (mWho->name().toStdString() + " " + mError).c_str();
}


Item::Item(const QString name, Item * parent, unsigned int options, ItemType type) :
    mName(name), mParent(parent), mOptions(options), mItemType(type)
{
}

Item::~Item() {
    qDeleteAll(mChildren);
}

void Item::childAdd(Item *item) {
    if(mOptions & CanHaveChildren)
        mChildren.push_back(item);
    else
        throw ItemOptionsMismatchException("Item can not have children", this);
}

Item* Item::childAt(int index) {
    if(index < mChildren.size())
        return mChildren.at(index);
    return nullptr;
}

void Item::childRemove(int index) {
    if(index < mChildren.size())
        mChildren.removeAt(index);
}

void Item::childRemoveAll() {
    qDeleteAll(mChildren);
    mChildren.clear();
}

int Item::row() {
    if(mParent)
        return mParent->mChildren.indexOf(static_cast<Item*>(this));
    return 0;
}

Item::RenameResult Item::rename(const QString &newName) {
    if(newName.isEmpty()) return Item::RenameResult::Empty;
    if(newName.length() > MAX_NAME_LENGTH) return Item::RenameResult::TooLong;
    if((mParent != nullptr) && !mParent->isNameUniqueAmongSiblings(newName, this)) return Item::RenameResult::Duplicate;

    mName = newName;
    return Item::RenameResult::Ok;
}

QString Item::display() const {
    return mName;
}

QVariant Item::decoration() const {
    return QVariant();
}

bool Item::isNameUniqueAmongSiblings(const QString &name, const Item *except) {
    for(const Item* i : mChildren) {
        if(i == except) continue;
        if(i->name().compare(name) == 0) return false;
    }

    return true;
}

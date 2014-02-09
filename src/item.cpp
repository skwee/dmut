#include "item.h"

Item::Item(const QString& name) :
    mParent(nullptr), mName(name)
{
}

Item::~Item() {
    qDeleteAll(mChildren);
}

int Item::rowCount() const {
    return mChildren.size();
}

int Item::columnCount() const {
    return 1;
}

int Item::rowIndex() const {
    if(mParent) return mParent->mChildren.indexOf(const_cast<Item*>(this));
    return 1;
}

QVariant Item::data(int role) const {
    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) return mName;
    return QVariant();
}

bool Item::setData(const QVariant &value, int column, int role) {
    return false;
}

Qt::ItemFlags Item::flags() const {
    return Qt::ItemFlags();
}

Item* Item::at(int index) const {
    if((index < 0) || (index >= mChildren.size())) return nullptr;
    return mChildren.at(index);
}

void Item::add(Item *item) {
    mChildren.push_back(item);
    item->mParent = this;
}

void Item::remove(Item *item) {
    if(mChildren.removeOne(item))
        delete item;
}

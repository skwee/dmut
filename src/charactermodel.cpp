#include "charactermodel.h"

CharacterModel::CharacterModel(Character* character, QObject *parent) :
    QAbstractItemModel(parent)
{
    mRoot = new RootItem();
    mRoot->add(character);
}

CharacterModel::~CharacterModel() {
    if(mRoot) delete mRoot;
}

int CharacterModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return static_cast<Item*>(parent.internalPointer())->rowCount();
    return mRoot->rowCount();
}

int CharacterModel::columnCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return static_cast<Item*>(parent.internalPointer())->columnCount();
    return mRoot->columnCount();
}

QModelIndex CharacterModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    Item* root = mRoot;
    if(parent.isValid())
        root = static_cast<Item*>(parent.internalPointer());

    if(Item* child = root->at(row))
        return createIndex(row, column, child);

    return QModelIndex();
}

QModelIndex CharacterModel::parent(const QModelIndex &child) const {
    if(!child.isValid())
        return QModelIndex();

    Item* childItem = static_cast<Item*>(child.internalPointer());
    Item* parentItem = childItem->parent();

    if(parentItem == mRoot) return QModelIndex();

    return createIndex(parentItem->rowIndex(), 0, parentItem);
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();
    return static_cast<Item*>(index.internalPointer())->data(index.column(), role);
}

bool CharacterModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;
    bool r = static_cast<Item*>(index.internalPointer())->setData(value, index.column(), role);

    if(r) emit dataChanged(index, index);

    return r;
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex &index) const {
    if(!index.isValid()) return Qt::ItemFlags();
    return static_cast<Item*>(index.internalPointer())->flags();
}

void CharacterModel::addItemTo(const QModelIndex &index) {
    Item* parent = mRoot;
    if(index.isValid()) {
        parent = static_cast<Item*>(index.internalPointer());
    }

    QModelIndex toIndex = index.isValid() ? index : QModelIndex();

    if(Item* child = parent->getNewChild()) {
        beginInsertRows(toIndex, parent->rowCount(), parent->rowCount());
        parent->add(child);
        endInsertRows();

        emit itemAdded(toIndex, parent, child);
    }
}

void CharacterModel::removeItem(const QModelIndex &index) {
    if(!index.isValid()) return;

    Item* item = static_cast<Item*>(index.internalPointer());
    if((item == mRoot) || (item == mRoot->at(0))) return;

    beginRemoveRows(index.parent(), item->rowIndex(), item->rowIndex());
    Item* parent = item->parent();
    parent->remove(item);
    endRemoveRows();
}

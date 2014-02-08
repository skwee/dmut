#include "charactermodel.h"

CharacterModel::CharacterModel(Character* root, QObject *parent) :
    QAbstractItemModel(parent), mRoot(root)
{}

CharacterModel::~CharacterModel() {
    if(mRoot) delete mRoot;
}

int CharacterModel::rowCount(const QModelIndex &parent) const {
    Item* parentItem = mRoot;

    if(parent.isValid()) {
        parentItem = static_cast<Item*>(parent.internalPointer());
        if(!parentItem) parentItem = mRoot;
    }

    return parentItem->rowCount();
}

int CharacterModel::columnCount(const QModelIndex &parent) const {
    Item* parentItem = mRoot;

    if(parent.isValid()) {
        parentItem = static_cast<Item*>(parent.internalPointer());
        if(!parentItem) parentItem = mRoot;
    }

    return parentItem->columnCount();
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

    if(parentItem == mRoot) {
        return QModelIndex();
    }

    return createIndex(parentItem->rowIndex(), 0, parentItem);
}

QVariant CharacterModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return mRoot->data(role);
    return static_cast<Item*>(index.internalPointer())->data(role);
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex &index) const {
    if(!index.isValid()) return mRoot->flags();
    return static_cast<Item*>(index.internalPointer())->flags();
}

void CharacterModel::addItemTo(const QModelIndex &index) {
    Item* parent = mRoot;
    if(index.isValid()) {
        parent = static_cast<Item*>(index.internalPointer());
    }

    if(Item* child = parent->getNewChild()) {
        beginInsertRows(index.isValid() ? index : QModelIndex(), parent->rowCount(), parent->rowCount());
        parent->add(child);
        endInsertRows();

        emit itemAdded(parent, child);
    }
}

#include "animationmodel.h"

AnimationModel::AnimationModel(QObject *parent) :
    QAbstractItemModel(parent), mRootItem(nullptr)
{
    mRootItem = new Item("AnimationsRootItem");
}

AnimationModel::~AnimationModel() {
    if(mRootItem) delete mRootItem;
}

int AnimationModel::rowCount(const QModelIndex &parent) const {
    Item* item = mRootItem;

    if(parent.isValid()) {
        item = static_cast<Item*>(parent.internalPointer());
        if(!item) item = mRootItem;
    }

    return item->childCount();
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    Item* item = static_cast<Item*>(index.internalPointer());

    if((role == Qt::DisplayRole) || (role == Qt::EditRole))
        return item->display();

    return QVariant();
}

bool AnimationModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;

    Item* item = static_cast<Item*>(index.internalPointer());

    if(role == Qt::EditRole) {
        const QString newName = value.toString();
        Item::RenameResult r = item->rename(newName);

        emit onNameChanged(r);
        return (r == Item::RenameResult::Ok) ? true : false;
    }

    return false;
}

Qt::ItemFlags AnimationModel::flags(const QModelIndex &index) const {
    Q_UNUSED(index);
    //@TODO
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex AnimationModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    Item* root = nullptr;
    if(parent.isValid())
        root = static_cast<Item*>(parent.internalPointer());
    else
        root = mRootItem;

    Item* child = root->childAt(row);

    if(child)
        return createIndex(row, column, child);

    return QModelIndex();
}

QModelIndex AnimationModel::parent(const QModelIndex &child) const {
    if(!child.isValid())
        return QModelIndex();

    Item* childItem = static_cast<Item*>(child.internalPointer());
    Item* parentItem = childItem->parent();

    if(parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant AnimationModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if((orientation == Qt::Horizontal) && (role == Qt::DisplayRole) && (section == 0)) {
        return tr("Name");
    }
    return QVariant();
}

bool AnimationModel::hasChildren(const QModelIndex &parent) const {
    Item* item = mRootItem;

    if(parent.isValid()) {
        item = static_cast<Item*>(parent.internalPointer());
        if(!item) item = mRootItem;
    }

    return item->childCount() > 0;
}

void AnimationModel::addAnimation() {
    beginInsertRows(QModelIndex(), mRootItem->childCount(), mRootItem->childCount());
    mRootItem->childAdd(new Animation(mRootItem));
    endInsertRows();
}

void AnimationModel::removeAnimation(const QModelIndex &index) {
    beginRemoveRows(QModelIndex(), index.row(), index.row());
    mRootItem->childRemove(index.row());
    endRemoveRows();
}

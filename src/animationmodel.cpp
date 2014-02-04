#include "animationmodel.h"

AnimationModel::AnimationModel(QObject *parent) :
    QAbstractItemModel(parent), mRootItem(nullptr)
{
    mRootItem = new Item(Block::ptr(), nullptr);
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

    return item->total();
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();
    if(index.column() != 0) return QVariant();

    Item* item = static_cast<Item*>(index.internalPointer());

    if((role == Qt::DisplayRole) || (role == Qt::EditRole))
        return item->display();
    else if(role == Qt::DecorationRole)
        return item->decoration();

    return QVariant();
}

bool AnimationModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;
    if(index.column() != 0) return false;

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
    if(!index.isValid()) return Qt::ItemFlags();

    Item* item = static_cast<Item*>(index.internalPointer());
    if(item) {
        Block::ptr block = item->block();
        if(block) {
            if(block->type() == Block::Type::Frame) {
                return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
            } else if(block->type() == Block::Type::Animation) {
                return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
            }
        }
    }

    return Qt::ItemFlags();
}

QModelIndex AnimationModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    Item* root = nullptr;
    if(parent.isValid())
        root = static_cast<Item*>(parent.internalPointer());
    else
        root = mRootItem;

    Item* child = root->at(row);

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

    return item->total() > 0;
}

bool AnimationModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) {
    if(sourceParent != destinationParent) return false;

    QModelIndex p = QModelIndex();
    Item* parent = mRootItem;

    if(sourceParent.isValid()) {
        parent = static_cast<Item*>(sourceParent.internalPointer());
        if(!parent) return false;
        p = sourceParent;
    }

    int destination = (destinationChild > sourceRow)
                ? (destinationChild + 1) : destinationChild;

    beginMoveRows(p, sourceRow, sourceRow, p, destination);
    bool flag = parent->swapItems(sourceRow, destinationChild);
    endMoveRows();
    return flag;
}

void AnimationModel::addAnimation() {
    beginInsertRows(QModelIndex(), mRootItem->total(), mRootItem->total());
    mRootItem->add(new Item(Block::ptr(new Animation)));
    endInsertRows();
}

void AnimationModel::removeAnimation(const QModelIndex &index) {
    beginRemoveRows(index.parent(), index.row(), index.row());
    mRootItem->remove(index.row());
    endRemoveRows();
}

void AnimationModel::addFrameToAnimation(const QModelIndex &animIndex, Block::ptr frame) {
    Item* item = mRootItem->at(animIndex.row());
    if(item) {
        if(item->contains(frame)) {
            emit frameAddFailedDuplicate();
            return;
        }

        beginInsertRows(animIndex, item->total(), item->total());
        item->add(new Item(frame));
        endInsertRows();
    }
}

void AnimationModel::remove(const QModelIndex &index) {
    Item* item = static_cast<Item*>(index.internalPointer());
    if(item) {
        int idx = item->indexOfSelf();
        if(idx >= 0) {
            beginRemoveRows(index.parent(), idx, idx);
            item->removeSelf();
            endRemoveRows();
        }
    }
}

void AnimationModel::removeAll() {
    beginRemoveRows(QModelIndex(), mRootItem->total(), mRootItem->total());
    mRootItem->removeAll();
    endRemoveRows();
}

bool AnimationModel::canBeMoved(const QModelIndex &index, int steps) const {
    if(!index.isValid()) return false;

    Item* item = static_cast<Item*>(index.internalPointer());
    if(!item || !item->parent()) return false;

    int itemIndex = item->indexOfSelf();

    if((itemIndex + steps) < 0) return false;
    if((itemIndex + steps) >= item->parent()->total()) return false;

    return true;
}

Block::Type AnimationModel::getBlockType(const QModelIndex &index) const {
    if(!index.isValid()) return Block::Type::None;

    Item* item = static_cast<Item*>(index.internalPointer());
    if(item && item->block()) {
        return item->block()->type();
    }
    return Block::Type::None;
}

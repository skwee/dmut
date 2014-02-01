#include "framemodel.h"

FrameModel::FrameModel(QObject *parent) :
    QAbstractItemModel(parent), mRootItem(nullptr)
{
    mRootItem = new Item(Block::ptr(), nullptr);
}

FrameModel::~FrameModel() {
    if(mRootItem) delete mRootItem;
}

int FrameModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mRootItem->total();
}

int FrameModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant FrameModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    Item* item = mRootItem->at(index.row());

    if(item) {
        if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
            return item->display();
        } else if(role == Qt::DecorationRole) {
            return item->decoration();
        }
    }

    return QVariant();
}

bool FrameModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;

    Item* item = mRootItem->at(index.row());

    if(item) {
        if(role == Qt::EditRole) {
            const QString newName = value.toString();
            Item::RenameResult r = item->rename(newName);
            emit onNameChange(r);
            return (r == Item::RenameResult::Ok) ? true : false;
        }
    }

    return false;
}

Qt::ItemFlags FrameModel::flags(const QModelIndex &index) const {
    Q_UNUSED(index);
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex FrameModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column);

    Item* item = mRootItem->at(row);
    if(item)
        return createIndex(row, column, item);

    return QModelIndex();
}

QModelIndex FrameModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

Block::ptr FrameModel::at(const QModelIndex &index) const {
    if(index.isValid()) {
        Item* item = mRootItem->at(index.row());
        if(item) {
            return item->block();
        }
    }

    return Block::ptr();
}

void FrameModel::add(const QPixmap& pixmap) {
    beginInsertRows(QModelIndex(), mRootItem->total(), mRootItem->total());
    mRootItem->add(new Item(Block::ptr(new Frame(pixmap))));
    endInsertRows();
}

void FrameModel::removeAll() {
    beginRemoveRows(QModelIndex(), 0, mRootItem->total());
    mRootItem->removeAll();
    endRemoveRows();
}

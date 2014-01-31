#include "framemodel.h"

FrameModel::FrameModel(QObject *parent) :
    QAbstractItemModel(parent), mRootItem(nullptr)
{
    mRootItem = new Item("FrameListRoot");
}

FrameModel::~FrameModel() {
    if(mRootItem) delete mRootItem;
}

int FrameModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mRootItem->childCount();
}

int FrameModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant FrameModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    Item* frame = mRootItem->childAt(index.row());

    if(frame) {
        if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
            return frame->display();
        } else if(role == Qt::DecorationRole) {
            return frame->decoration();
        }
    }

    return QVariant();
}

bool FrameModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;

    Item* frame = mRootItem->childAt(index.row());

    if(frame) {
        if(role == Qt::EditRole) {
            const QString newName = value.toString();

            Item::RenameResult r = frame->rename(newName);

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

    Item* frame = mRootItem->childAt(row);
    if(frame)
        return createIndex(row, column, frame);

    return QModelIndex();
}

QModelIndex FrameModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

Frame* FrameModel::at(const QModelIndex &index) const {
    if(!index.isValid()) return nullptr;
    return static_cast<Frame*>(mRootItem->childAt(index.row()));
}

void FrameModel::add(const QPixmap& pixmap) {
    beginInsertRows(QModelIndex(), mRootItem->childCount(), mRootItem->childCount());
    mRootItem->childAdd(new Frame(pixmap, mRootItem));
    endInsertRows();
}

void FrameModel::removeAll() {
    beginRemoveRows(QModelIndex(), 0, mRootItem->childCount());
    mRootItem->childRemoveAll();
    endRemoveRows();
}

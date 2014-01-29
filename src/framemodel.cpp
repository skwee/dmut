#include "framemodel.h"

FrameModel::FrameModel(const Frame::Options& frameOptions, QObject *parent) :
    QAbstractItemModel(parent), mFrameOptions(frameOptions)
{
}

FrameModel::~FrameModel() {
}

int FrameModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mFrameList.size();
}

int FrameModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant FrameModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    Frame::Ptr frame = mFrameList.at(index.row());

    if(frame) {
        if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
            return frame->getName();
        } else if(role == Qt::DecorationRole) {
            return frame->getPixmap();
        }
    }

    return QVariant();
}

bool FrameModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;

    Frame::Ptr frame = mFrameList.at(index.row());

    if(frame) {
        if(role == Qt::EditRole) {
            const QString newName = value.toString();
            if(newName.isEmpty()) {
                emit invalidName(InvalidNameReason::Empty);
                return false;
            } else if(!isNameUnique(newName, frame)) {
                emit invalidName(InvalidNameReason::Duplicate);
                return false;
            }
            frame->setName(newName);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags FrameModel::flags(const QModelIndex &index) const {
    if(!index.isValid())
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    Frame::Ptr frame = mFrameList.at(index.row());
    if(frame->isActive())
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    return Qt::ItemFlags();
}

QModelIndex FrameModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column);

    Frame::Ptr frame = mFrameList.at(row);
    if(frame)
        return createIndex(row, column, frame.get());

    return QModelIndex();
}

QModelIndex FrameModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

Frame::Ptr FrameModel::frameAt(const QModelIndex &index) const {
    if(!index.isValid() || (index.row() >= mFrameList.size())) return Frame::Ptr();

    return mFrameList.at(index.row());
}

void FrameModel::addFrame(const QPixmap& pixmap) {
    int l = mFrameList.size();
    beginInsertRows(QModelIndex(), l, l);
    mFrameList.push_back(Frame::Ptr(new Frame(pixmap)));
    endInsertRows();
}

bool FrameModel::isNameUnique(const QString &name, Frame::Ptr ingore) const {
    for(const Frame::Ptr f : mFrameList) {
        if(f == ingore) continue;
        if(f->getName().compare(name) == 0) return false;
    }

    return true;
}

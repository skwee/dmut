#include "framemodel.h"

FrameModel::FrameModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

FrameModel::~FrameModel() {
    qDeleteAll(mFrameList);
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

    Frame* frame = mFrameList.at(index.row());

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

    Frame* frame = mFrameList.at(index.row());

    if(frame) {
        if(role == Qt::EditRole) {
            const QString newName = value.toString();
            bool status = true;
            Frame::Namer::NameValidity nv = Frame::Namer::validate(newName);

            if(nv != Frame::Namer::NameValidity::Valid) {
                status = false;
            } else if(!isNameUnique(newName, frame)) {
                nv = Frame::Namer::NameValidity::Duplicate;
                status = false;
            } else {
                nv = Frame::Namer::NameValidity::Valid;
            }

            if(status) {
                frame->setName(newName);
            }

            emit nameChangeAttempt(status, nv);
            return status;
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

    Frame* frame = mFrameList.at(row);
    if(frame)
        return createIndex(row, column, frame);

    return QModelIndex();
}

QModelIndex FrameModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

Frame* FrameModel::at(const QModelIndex &index) const {
    if(!index.isValid() || (index.row() >= mFrameList.size())) return nullptr;

    return mFrameList.at(index.row());
}

void FrameModel::add(const QPixmap& pixmap) {
    int l = mFrameList.size();
    beginInsertRows(QModelIndex(), l, l);
    mFrameList.push_back(new Frame(pixmap));
    endInsertRows();
}

void FrameModel::removeAll() {
    beginRemoveRows(QModelIndex(), 0, mFrameList.size());
    qDeleteAll(mFrameList);
    mFrameList.clear();
    endRemoveRows();
}

bool FrameModel::isNameUnique(const QString &name, const Frame* const ingore) const {
    for(const Frame* const f : mFrameList) {
        if(f == ingore) continue;
        if(f->getName().compare(name) == 0) return false;
    }

    return true;
}

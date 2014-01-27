#include "framemodel.h"

FrameModel::FrameModel(const QString& frameFileName, const Frame::Options& options, QObject *parent) :
    QAbstractItemModel(parent), mFrameSet(nullptr)
{
    mFrameSet = new FrameSet(frameFileName, options);
}

FrameModel::~FrameModel() {
    if(mFrameSet != nullptr)
        delete mFrameSet;
}

int FrameModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mFrameSet->totalItems();
}

int FrameModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant FrameModel::data(const QModelIndex &index, int role) const {
    Frame* frame = frameAt(index);

    if(frame != nullptr) {
        if(role == Qt::DisplayRole) {
            return frame->getName();
        } else if(role == Qt::DecorationRole) {
            return frame->getPixmap();
        }
    }

    return QVariant();
}

bool FrameModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    Frame* frame = frameAt(index);
    if(frame != nullptr) {
        if(role == Qt::EditRole) {
            const QString newName = value.toString();
            if(newName.isEmpty()) {
                emit invalidName(InvalidNameReason::Empty);
                return false;
            } else if(!mFrameSet->isNameUnique(newName, frame)) {
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
    Q_UNUSED(index);
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex FrameModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column);

    Frame* frame = frameAt(parent);
    if(frame != nullptr)
        return createIndex(row, column, frame);

    return QModelIndex();
}

QModelIndex FrameModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

Frame* FrameModel::frameAt(const QModelIndex &index) const {
    if(!index.isValid()) return nullptr;
    if(index.row() >= mFrameSet->totalItems()) return nullptr;
    return mFrameSet->frameAt(index.row());
}

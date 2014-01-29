#include "animationframemodel.h"

AnimationFrameModel::AnimationFrameModel(QObject *parent) :
    QAbstractItemModel(parent), mAnimationFrameList(nullptr)
{
}

AnimationFrameModel::~AnimationFrameModel() {}

int AnimationFrameModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return (mAnimationFrameList) ? mAnimationFrameList->size() : 0;
}

int AnimationFrameModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant AnimationFrameModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || !mAnimationFrameList || (index.row() >= mAnimationFrameList->size()))
        return QVariant();

    const AnimationFrame& af = mAnimationFrameList->at(index.row());

    if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
        return (index.column() == 1) ? af.getName() : QString::number(af.getDuration());
    }

    return QVariant();
}

bool AnimationFrameModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || !mAnimationFrameList || (index.row() >= mAnimationFrameList->size()))
        return false;

    const AnimationFrame& af = mAnimationFrameList->at(index.row());

    //@TODO

    return false;
}

Qt::ItemFlags AnimationFrameModel::flags(const QModelIndex &index) const {
    //@TODO
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex AnimationFrameModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid() || !mAnimationFrameList || (row >= mAnimationFrameList->size()))
        return createIndex(row, column);

//    const AnimationFrame& af = mAnimationFrameList->at(row);
//    return createIndex(row, column, af);

    return QModelIndex();
}

QModelIndex AnimationFrameModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

void AnimationFrameModel::setList(const AnimationFrame::List * const list) {
    if(mAnimationFrameList) {
        beginRemoveRows(QModelIndex(), 0, mAnimationFrameList->size());
        mAnimationFrameList = nullptr;
        endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, list->size());
    mAnimationFrameList = list;
    endInsertRows();
}

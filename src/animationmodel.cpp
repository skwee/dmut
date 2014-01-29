#include "animationmodel.h"

AnimationModel::AnimationModel(QObject* parent) :
    QAbstractItemModel(parent)
{
}

AnimationModel::~AnimationModel() {}

int AnimationModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mAnimationList.size();
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    Animation::Ptr animation = mAnimationList.at(index.row());

    if(animation) {
        if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
            return animation->getName();
        }
    }

    return QVariant();
}

bool AnimationModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid()) return false;

    Animation::Ptr animation = mAnimationList.at(index.row());

    if(animation) {
        if(role == Qt::EditRole) {
            const QString newName = value.toString();
            if(newName.isEmpty()) {
                emit invalidName(InvalidNameReason::Empty);
                return false;
            } else if(!isNameUnique(newName, animation)) {
                emit invalidName(InvalidNameReason::Duplicate);
                return false;
            }
            animation->setName(newName);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags AnimationModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex AnimationModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column);

    Animation::Ptr animation = mAnimationList.at(row);
    if(animation)
        return createIndex(row, column, animation.get());

    return QModelIndex();
}

QModelIndex AnimationModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

void AnimationModel::addAnimation() {
    int l = mAnimationList.size();
    beginInsertRows(QModelIndex(), l, l);
    mAnimationList.push_back(Animation::Ptr(new Animation));
    endInsertRows();
}

void AnimationModel::removeAnimation(Animation::Ptr animation) {
    unsigned int idx = 0;
    for(Animation::Ptr a : mAnimationList) {
        if(a == animation) break;
        idx++;
    }
    beginRemoveRows(QModelIndex(), idx, idx);
    mAnimationList.erase(mAnimationList.begin() + idx);
    endRemoveRows();
}

void AnimationModel::removeAnimation(const QModelIndex &index) {
    if(!index.isValid()) return;
    if(index.row() >= mAnimationList.size()) return;

    removeAnimation(mAnimationList.at(index.row()));
}

void AnimationModel::addFrame(const QModelIndex &index, Frame::Ptr frame) {
    if(!index.isValid()) return;
    if(index.row() >= mAnimationList.size()) return;

    Animation::Ptr a = mAnimationList.at(index.row());
    a->addFrame(frame);
    emit onFrameAdded(a, frame);
}

bool AnimationModel::isNameUnique(const QString &name, Animation::Ptr ingore) const {
    for(const Animation::Ptr a : mAnimationList) {
        if(a == ingore) continue;
        if(a->getName().compare(name) == 0) return false;
    }

    return true;
}

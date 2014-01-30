#include "animationmodel.h"

AnimationModel::AnimationModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

AnimationModel::~AnimationModel() {
    qDeleteAll(mAnimationList);
}

int AnimationModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid() && (parent.row() < mAnimationList.size())) {
        return mAnimationList.at(parent.row())->totalFrames();
    }

    return mAnimationList.size();
}

int AnimationModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant AnimationModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    if(index.parent().isValid() && index.parent().row() < mAnimationList.size()) {
        const AnimationFrame* af = mAnimationList.at(index.parent().row())->frameAt(index.row());
        if(af) {
            if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
                if(index.column() == 0) {
                    return af->frame()->getName();
                }
            }
        }
    } else {
        Animation* animation = mAnimationList.at(index.row());

        if(animation) {
            if((role == Qt::DisplayRole) || (role == Qt::EditRole)) {
                switch(index.column()) {
                case 0:
                    return animation->getName();
                    break;
                case 1:
                    return QString::number(animation->getFramesPerSecond());
                    break;
                }
            }
        }
    }


    return QVariant();
}

bool AnimationModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(!index.isValid() || index.parent().isValid()) return false;

    Animation* animation = mAnimationList.at(index.row());

    if(animation) {
        if(role == Qt::EditRole) {
            if(index.column() == 0) { //name
                const QString newName = value.toString();
                bool status = true;

                Animation::Namer::NameValidity nv = Animation::Namer::validate(newName);

                if(nv != Animation::Namer::NameValidity::Valid) {
                    status = false;
                } else if(!isNameUnique(newName, animation)) {
                    nv = Animation::Namer::NameValidity::Duplicate;
                    status = false;
                } else {
                    nv = Animation::Namer::NameValidity::Valid;
                }

                if(status) {
                    animation->setName(newName);
                }

                emit nameChangeAttempt(status, nv);
                return status;
            } else if(index.column() == 1) { //fps
                Animation::FramesPerSecond fps = static_cast<Animation::FramesPerSecond>(value.toInt());
                animation->setFramesPerSecond(fps);
                emit framePerSecondChanged(animation, fps);
                return true;
            }
        }
    }

    return false;
}

Qt::ItemFlags AnimationModel::flags(const QModelIndex &index) const {
    Q_UNUSED(index);
    //@TODo
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex AnimationModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid())
        return createIndex(row, column, mAnimationList.at(row));

    Animation* animation = mAnimationList.at(parent.row());
    AnimationFrame* af = animation->frameAt(row);
    if(af) return createIndex(row, column, af);

    return QModelIndex();
}

#include <QDebug>

QModelIndex AnimationModel::parent(const QModelIndex &child) const {
    Animation* animation = static_cast<Animation*>(child.internalPointer());
    if(child.row() < animation->totalFrames()) qDebug() << animation->frameAt(child.row());
    if(animation) {
//        return createIndex(child.row(), child.column(), animation->frameAt(child.row()));
    }
    return QModelIndex();
}

QVariant AnimationModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if((orientation == Qt::Horizontal) && (role == Qt::DisplayRole)) {
        return (section == 0) ? tr("Name") : tr("Frames per second");
    }
    return QVariant();
}

void AnimationModel::addAnimation() {
    int s = mAnimationList.size();
    beginInsertRows(QModelIndex(), s, s);
    mAnimationList.push_back(new Animation());
    endInsertRows();
}

void AnimationModel::removeAnimation(const QModelIndex &index) {
    if(index.isValid() && (index.row() < mAnimationList.size())) {
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        mAnimationList.removeAt(index.row());
        endRemoveRows();
    }
}

void AnimationModel::addFrameToAnimation(const QModelIndex &animIndex, Frame * sprite) {
    if(animIndex.isValid() && (animIndex.row() < mAnimationList.size())) {
        Animation* a = mAnimationList.at(animIndex.row());
        beginInsertRows(animIndex, a->totalFrames(), a->totalFrames());
        a->addFrame(sprite);
        endInsertRows();
    }
}

bool AnimationModel::isNameUnique(const QString &name, const Animation* const ingore) const {
    for(const Animation* const a : mAnimationList) {
        if(a == ingore) continue;
        if(a->getName().compare(name) == 0) return false;
    }

    return true;
}

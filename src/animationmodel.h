#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include <QAbstractItemModel>
#include <vector>

#include "animation.h"

class AnimationModel: public QAbstractItemModel {
    Q_OBJECT
public:
    enum class InvalidNameReason {
        Empty,
        Duplicate
    };

    AnimationModel(QObject* parent = 0);
    ~AnimationModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    void addAnimation();
    void removeAnimation(Animation::Ptr animation);
    void removeAnimation(const QModelIndex& index);

    void addFrame(const QModelIndex& index, Frame::Ptr frame);

signals:
    void onFrameAdded(Animation::Ptr toAnimation, Frame::Ptr frame);
    void invalidName(AnimationModel::InvalidNameReason reason);

private:
    bool isNameUnique(const QString& name, Animation::Ptr ingore) const;

    std::vector<Animation::Ptr> mAnimationList;
};

#endif // ANIMATIONMODEL_H

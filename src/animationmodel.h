#ifndef ANIMATIONMODEL_H
#define ANIMATIONMODEL_H

#include <QAbstractItemModel>

#include "animation.h"

class AnimationModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit AnimationModel(QObject *parent = 0);
    ~AnimationModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void addAnimation();
    void removeAnimation(const QModelIndex& index);

    void addFrameToAnimation(const QModelIndex& animIndex, Frame* sprite);

signals:
    void nameChangeAttempt(bool succeed, Animation::Namer::NameValidity reason);
    void framePerSecondChanged(const Animation* const animation, Animation::FramesPerSecond fps);

private:
    bool isNameUnique(const QString& name, const Animation* const ingore) const;

    QList<Animation*> mAnimationList;
};

#endif // ANIMATIONMODEL_H

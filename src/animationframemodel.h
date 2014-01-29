#ifndef ANIMATIONFRAMEMODEL_H
#define ANIMATIONFRAMEMODEL_H

#include <QAbstractItemModel>

#include "animationframe.h"

class AnimationFrameModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit AnimationFrameModel(QObject *parent = 0);
    ~AnimationFrameModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    void setList(const AnimationFrame::List* const list);

private:
    const AnimationFrame::List* mAnimationFrameList;
};

#endif // ANIMATIONFRAMEMODEL_H

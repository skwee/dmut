#ifndef ANIMATIONITEMDELEGATE_H
#define ANIMATIONITEMDELEGATE_H

#include <QItemDelegate>

class AnimationItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit AnimationItemDelegate(QObject *parent = 0);

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

};

#endif // ANIMATIONITEMDELEGATE_H

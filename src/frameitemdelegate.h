#ifndef FRAMEITEMDELEGATE_H
#define FRAMEITEMDELEGATE_H

#include <QItemDelegate>

class FrameItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit FrameItemDelegate(QObject *parent = 0);

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

};

#endif // FRAMEITEMDELEGATE_H

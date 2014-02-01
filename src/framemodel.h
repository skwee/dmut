#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QAbstractItemModel>

#include "frame.h"
#include "item.h"

class FrameModel: public QAbstractItemModel {
    Q_OBJECT
public:
    FrameModel(QObject* parent = 0);
    ~FrameModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    Block::ptr at(const QModelIndex& index) const;
    void add(const QPixmap& pixmap);
    void removeAll();

signals:
    void onNameChange(Item::RenameResult result);

private:
    Item* mRootItem;
};

#endif // FRAMEMODEL_H

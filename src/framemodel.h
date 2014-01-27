#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QAbstractListModel>

#include "frameset.h"

class FrameModel: public QAbstractListModel {
    Q_OBJECT
public:
    enum class InvalidNameReason {
        Empty,
        Duplicate
    };

    FrameModel(FrameSet* frameSet, QObject* parent = 0);
    ~FrameModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

signals:
    void invalidName(FrameModel::InvalidNameReason reason);

private:
    Frame* frameAt(const QModelIndex& index) const;

private:
    FrameSet* mFrameSet;
};

#endif // FRAMEMODEL_H

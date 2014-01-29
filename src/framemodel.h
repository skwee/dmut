#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QAbstractItemModel>
#include <vector>

#include "frame.h"

class FrameModel: public QAbstractItemModel {
    Q_OBJECT
public:
    enum class InvalidNameReason {
        Empty,
        Duplicate
    };

    FrameModel(const Frame::Options& frameOptions, QObject* parent = 0);
    ~FrameModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    Frame::Ptr frameAt(const QModelIndex &index) const;

    void addFrame(const QPixmap& pixmap);

signals:
    void invalidName(FrameModel::InvalidNameReason reason);

private:
    bool isNameUnique(const QString& name, Frame::Ptr ingore) const;

    Frame::Options mFrameOptions;
    std::vector<Frame::Ptr> mFrameList;
};

#endif // FRAMEMODEL_H

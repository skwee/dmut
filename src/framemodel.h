#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <QAbstractItemModel>
#include <memory>

#include "frame.h"

class FrameModel: public QAbstractItemModel {
    Q_OBJECT
public:
    enum class InvalidNameReason {
        Empty,
        Duplicate
    };

    typedef std::shared_ptr<Frame> FramePtr;

    FrameModel(const Frame::Options& frameOptions, QObject* parent = 0);
    ~FrameModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    void addFrame(const QPixmap& pixmap);

signals:
    void invalidName(FrameModel::InvalidNameReason reason);

private:
    bool isNameUnique(const QString& name, FramePtr ingore) const;

    Frame::Options mFrameOptions;
    QList<FramePtr> mFrameList;
};

#endif // FRAMEMODEL_H

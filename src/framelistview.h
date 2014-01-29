#ifndef FRAMELISTWIDGET_H
#define FRAMELISTWIDGET_H

#include <QListView>

#include "spritetoframefactory.h"
#include "framemodel.h"

class FrameListView : public QListView
{
    Q_OBJECT
public:
    explicit FrameListView(QWidget *parent = 0);
    ~FrameListView();

    void createNewFrameList(const QString& spriteFileName, const Frame::Options& frameOptions);

signals:
    void onFrameDoubleClicked(Frame::Ptr frme);

private slots:
    void onInvalidName(FrameModel::InvalidNameReason reason);
    void onDoubleClicked(const QModelIndex& index);

private:
    FrameModel* mModel;
};

#endif // FRAMELISTWIDGET_H

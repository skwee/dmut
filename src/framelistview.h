#ifndef FRAMELISTWIDGET_H
#define FRAMELISTWIDGET_H

#include <QListView>
#include <QStandardItemModel>

#include "frame.h"
#include "frameset.h"
#include "framemodel.h"

class FrameListView : public QListView
{
    Q_OBJECT
public:
    explicit FrameListView(QWidget *parent = 0);
    virtual ~FrameListView();

    void populate(const QString& spriteFileName, const Frame::Options& frameOptions);

private slots:
    void onInvalidNameSet(FrameModel::InvalidNameReason reason);

private:
    FrameModel* mModel;
};

#endif // FRAMELISTWIDGET_H

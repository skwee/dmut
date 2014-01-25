#ifndef FRAMELISTWIDGET_H
#define FRAMELISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>

#include "frame.h"
#include "frameset.h"

class FrameListItem: public QListWidgetItem {
public:
    FrameListItem(Frame* frame);

    Frame* getFrame() const { return mFrame; }

    void setNameFromFrame();
    void setNameFromItem();

private:
    Frame* mFrame;
};

class FrameListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit FrameListWidget(QWidget *parent = 0);

    void populate(const QString& spriteFileName, const Frame::Options& frameOptions);

signals:

private slots:
    void onItemChanged(QListWidgetItem* item);

private:
    FrameSet* mFrameSet;
    bool mIgnoreDuplicateNameCheck;
};

#endif // FRAMELISTWIDGET_H

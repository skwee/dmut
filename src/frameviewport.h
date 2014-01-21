#ifndef FRAMEVIEWPORT_H
#define FRAMEVIEWPORT_H

#include <QGraphicsView>

#include "frameset.h"

class FrameViewport : public QGraphicsView
{
    Q_OBJECT
public:
    explicit FrameViewport(QWidget *parent = 0);
    ~FrameViewport();

    void startNewSession(const QString& spriteFileName, const Frame::Options& options);

signals:
    void selectedFrameChanged(Frame* previous, Frame* current);

public slots:
    void mousePressEvent(QMouseEvent* e);
    void keyPressEvent(QKeyEvent* e);

private:
    void yeildFrameSelectionChanged();

    QGraphicsScene* mScene;
    FrameSet* mFrameSet;
    QGraphicsRectItem* mSelectionRect;
    Frame* mActiveFrame;
};

#endif // FRAMEVIEWPORT_H

#ifndef DMUTVIEWPORT_H
#define DMUTVIEWPORT_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "dmut.h"

class DmutViewport : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DmutViewport(QWidget *parent = 0);
    ~DmutViewport();

    void startNewSession(const QString& filename, const Dmut::Data& data);

signals:

public slots:
    void mousePressEvent(QMouseEvent* e);

private:
    Dmut* mDmut;
    QGraphicsScene* mScene;
};

#endif // DMUTVIEWPORT_H

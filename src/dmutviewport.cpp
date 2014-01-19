#include "dmutviewport.h"

DmutViewport::DmutViewport(QWidget *parent) :
    QGraphicsView(parent), mDmut(nullptr)
{
    mScene = new QGraphicsScene();
    setScene(mScene);
}

DmutViewport::~DmutViewport() {
    if(mDmut != nullptr) delete mDmut;
    if(mScene != nullptr) delete mScene;
}

void DmutViewport::startNewSession(const QString &filename, const Dmut::Data &data) {
    if(mDmut != nullptr) delete mDmut;

    mDmut = new Dmut(filename, data);

    mScene->clear();

    QList<Dmut::Item> items = mDmut->getItems();
    for(auto item: items) {
        mScene->addItem(item.data());
    }

    resize(mScene->itemsBoundingRect().size().width(), mScene->itemsBoundingRect().size().height());

    show();
}

void DmutViewport::mousePressEvent(QMouseEvent *e) {
    QPointF pt = mapToScene(e->pos());

    int x = ((unsigned int)pt.x() / mDmut->getData().frame.w) * mDmut->getData().frame.w;
    int y = ((unsigned int)pt.y() / mDmut->getData().frame.h) * mDmut->getData().frame.h;

    mScene->addRect(x, y, mDmut->getData().frame.w, mDmut->getData().frame.h, QPen(), QBrush(QColor(128, 128, 255, 128)));
}

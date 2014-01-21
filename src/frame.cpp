#include "frame.h"

unsigned int Frame::idx = 0;

Frame::Frame(const QPixmap &pixmap, qreal x, qreal y) :
    mPixmap(nullptr), mStatusRect(nullptr), mAddedToScene(false),
    mGroupName(""), mName(""), mIndex(0)
{
    mPixmap = new QGraphicsPixmapItem();
    mPixmap->setPixmap(pixmap);
    mPixmap->setPos(x, y);

    mStatusRect = new QGraphicsRectItem();
    mStatusRect->setRect(0, 0, pixmap.width(), pixmap.height());
    mStatusRect->setPen(QPen(QColor(0, 0, 0)));
    mStatusRect->setPos(x, y);
}

Frame::~Frame() {
    if(!mAddedToScene) {
        if(mPixmap != nullptr) delete mPixmap;
        if(mStatusRect != nullptr) delete mStatusRect;
    }
}

void Frame::addToScene(QGraphicsScene * const scene) {
    scene->addItem(mPixmap);
    scene->addItem(mStatusRect);
    mAddedToScene = true;
}

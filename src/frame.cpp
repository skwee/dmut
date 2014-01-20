#include "frame.h"

unsigned int Frame::idx = 0;

Frame::Frame(const QPixmap &pixmap, qreal x, qreal y) :
    mPixmap(nullptr), mStatusRect(nullptr), mAddedToScene(false)
{
    mPixmap = new QGraphicsPixmapItem();
    mPixmap->setPixmap(pixmap);
    mPixmap->setPos(x, y);

    mStatusRect = new QGraphicsRectItem();
    mStatusRect->setBrush(NOT_VALID_BRUSH);
    mStatusRect->setPos(x, y);

    mGroupName = QString("group %d").arg(idx++);
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

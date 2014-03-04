#include "sprite.h"

Sprite::Sprite(const QPixmap &pixmap, const Offset &offset, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    mOffset(offset)
{
    setPixmap(pixmap);
    setPos(offset.x, offset.y);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        scene()->clearSelection();
        setSelected(true);
    } else {
        event->ignore();
    }
}

void Sprite::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(event->scenePos() == event->buttonDownScenePos(Qt::LeftButton)) {
        scene()->clearSelection();
        setSelected(true);
    }
}

void Sprite::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    mousePressEvent(event);
    QList<QGraphicsItem*> selected = scene()->selectedItems();
    if(selected.length() == 1) {
        //TODO emit event on scene object
    }
}

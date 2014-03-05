#include "sprite.h"
#include "spriteatlasscene.h"

Sprite::Sprite(const QPixmap &pixmap, const Offset &offset, QGraphicsItem* parent) :
    QGraphicsPixmapItem(parent),
    mOffset(offset)
{
    mUuid = QUuid::createUuid();
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
    if(scene()->selectedItems().length() > 0) {
        emit static_cast<SpriteAtlasScene*>(scene())->onItemSelected();
    }
}

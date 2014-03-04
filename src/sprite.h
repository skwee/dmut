#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

class Sprite: public QGraphicsPixmapItem
{
public:
    typedef struct {
        unsigned int width;
        unsigned int height;
    }Size;

    typedef struct {
        unsigned int x;
        unsigned int y;
    }Offset;

    Sprite(const QPixmap& pixmap, const Offset& offset, QGraphicsItem* parent = 0);

    inline Offset offset() const { return mOffset; }

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
    Offset mOffset;
};

#endif // SPRITE_H

#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QUuid>

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

    inline QUuid uuid() const { return mUuid; }

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);

private:
    Offset mOffset;
    QUuid mUuid;
};

Q_DECLARE_METATYPE(Sprite*)

#endif // SPRITE_H

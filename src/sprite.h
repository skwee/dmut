#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>

class Sprite
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

    Sprite(const QPixmap& pixmap, const Offset& offset);

    inline QPixmap pixmap() const { return mPixmap; }
    inline Offset offset() const { return mOffset; }

private:
    QPixmap mPixmap;
    Offset mOffset;
};

#endif // SPRITE_H

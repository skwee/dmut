#include "dmut.h"

Dmut::Dmut(const QString& filename, const Data& data) :mData(data)
{
    QPixmap sprite(filename);
    int w = sprite.width() - data.frame.w;
    int h = sprite.height() - data.frame.h;

    for(int j = 0; j <= h; j += data.frame.h) {
        for(int i = 0; i <= w; i += data.frame.w) {
            Item item(new QGraphicsPixmapItem());
            item->setPixmap(sprite.copy(i, j, data.frame.w, data.frame.h));
            item->setPos(i, j);

            mItems.append(item);
        }
    }
}

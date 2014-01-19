#ifndef DMUT_H
#define DMUT_H

#include <QGraphicsPixmapItem>

class Dmut
{
public:
    typedef struct {
        QString name;
        struct {
            unsigned int w;
            unsigned int h;
        }frame;
    }Data;

    typedef QSharedPointer<QGraphicsPixmapItem> Item;

public:
    Dmut(const QString& filename, const Data& data);

    QList<Item> getItems() const { return mItems; }

    const Data& getData() const { return mData; }

private:
    Data mData;
    QList<Item> mItems;
};

#endif // DMUT_H

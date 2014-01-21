#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Frame
{
public:
    static unsigned int idx;

    typedef struct {
        unsigned int width;
        unsigned int height;
    }Options;

    Frame(const QPixmap& pixmap, qreal x, qreal y);
    ~Frame();

    void addToScene(QGraphicsScene* const scene);

    const QString& getGroupName() const { return mGroupName; }
    const QString& getName() const { return mName;}
    unsigned int getIndex() const { return mIndex; }

    void setGroupName(const QString& name) { mGroupName = name; }
    void setName(const QString& name) { mName = name; }
    void setIndex(unsigned int index) { mIndex = index; }

private:
    QGraphicsPixmapItem* mPixmap;
    QGraphicsRectItem* mStatusRect;
    bool mAddedToScene;

    QString mGroupName, mName;
    unsigned int mIndex;
};

#endif // FRAME_H

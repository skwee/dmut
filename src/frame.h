#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Frame
{
public:
    static unsigned int idx;

    const QBrush VALID_BRUSH = QBrush(QColor(128, 255, 128, 128));
    const QBrush NOT_VALID_BRUSH = QBrush(QColor(255, 128, 128, 128));

    typedef struct {
        unsigned int width;
        unsigned int height;
    }Options;

    Frame(const QPixmap& pixmap, qreal x, qreal y);
    ~Frame();

    void addToScene(QGraphicsScene* const scene);

    const QString& getGroupName() const { return mGroupName; }
    const QString& getName() const { return mName;}

    void setGroupName(const QString& name) { mGroupName = name; }
    void setName(const QString& name) { mName = name; }

private:
    QGraphicsPixmapItem* mPixmap;
    QGraphicsRectItem* mStatusRect;
    bool mAddedToScene;

    QString mGroupName, mName;
};

#endif // FRAME_H

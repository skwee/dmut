#ifndef FRAME_H
#define FRAME_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Frame: public QObject
{
    Q_OBJECT

private:
    static unsigned int sFrameIndex;

public:
    typedef struct {
        unsigned int width;
        unsigned int height;
    }Options;

    Frame(const QPixmap& pixmap, qreal x, qreal y);
    virtual ~Frame();

    void addToScene(QGraphicsScene* const scene);

    const QString& getName() const { return mName;}
    void setName(const QString& name);

    QGraphicsView* getView() const {return mPixmap->scene()->views().first(); }
    QPointF getPosition() const { return mPixmap->mapToScene(mPixmap->boundingRect().bottomRight()); }
    QRectF getDimensions() const { return mPixmap->boundingRect(); }

signals:
    void nameChanged(Frame* frame);

private:
    QGraphicsPixmapItem* mPixmap;
    QGraphicsRectItem* mStatusRect;
    bool mAddedToScene;

    QString mName;
};

#endif // FRAME_H

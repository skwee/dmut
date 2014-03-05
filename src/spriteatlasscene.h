#ifndef SPRITEATLASSCENE_H
#define SPRITEATLASSCENE_H

#include <QGraphicsScene>

#include "sprite.h"

class SpriteAtlasScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SpriteAtlasScene(QObject *parent = 0);

    Sprite* selectedItem() const;

signals:
    void onItemSelected();
};

#endif // SPRITEATLASSCENE_H

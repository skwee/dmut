#include "spriteatlasscene.h"

SpriteAtlasScene::SpriteAtlasScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

Sprite* SpriteAtlasScene::selectedItem() const {
    if(selectedItems().length() > 0) {
        return static_cast<Sprite*>(selectedItems().first());
    }
    return nullptr;
}

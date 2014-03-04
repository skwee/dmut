#include "spriteatlasmodel.h"

SpriteAtlasModel::SpriteAtlasModel(const QString &fileName, const Sprite::Size &size)
{
    QPixmap sprite(fileName);

    unsigned int rows = sprite.width() / size.width;
    unsigned int columns = sprite.height() / size.height;

    for(unsigned int i = 0; i < rows; ++i) {
        for(unsigned int j = 0; j < columns; ++j) {
            Sprite::Offset o;
            o.x = i * size.width;
            o.y = j * size.height;

            mAtlas.push_back(
                        new Sprite(
                            sprite.copy(o.x, o.y, size.width, size.height),
                            o
                            )
                        );
        }
    }
}

SpriteAtlasModel::~SpriteAtlasModel() {
    mAtlas.clear();
}

#ifndef SPRITEATLASMODEL_H
#define SPRITEATLASMODEL_H

#include <QString>
#include <QList>

#include "sprite.h"

class SpriteAtlasModel
{
public:
    explicit SpriteAtlasModel(const QString &fileName, const Sprite::Size &size);
    ~SpriteAtlasModel();

    inline const QList<Sprite*> items() const { return mAtlas; }

private:
    QList<Sprite*> mAtlas;
};

#endif // SPRITEATLASMODEL_H

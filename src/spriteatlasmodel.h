#ifndef SPRITEATLASMODEL_H
#define SPRITEATLASMODEL_H

#include <QAbstractItemModel>

#include "sprite.h"

class SpriteAtlasModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SpriteAtlasModel(QObject *parent = 0);
    ~SpriteAtlasModel();

    void create(const QString &fileName, const Sprite::Size &size);
    void clear();

    inline Sprite::Size size() const { return mAtlasSize; }
    inline Sprite::Size spriteSize() const { return mSpriteSize; }

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<Sprite*> mAtlas;
    Sprite::Size mSpriteSize;
    Sprite::Size mAtlasSize;
};

#endif // SPRITEATLASMODEL_H

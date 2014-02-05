#include "spriteatlasmodel.h"

SpriteAtlasModel::SpriteAtlasModel(QObject *parent) :
    QAbstractItemModel(parent)
{}

SpriteAtlasModel::~SpriteAtlasModel() {
    qDeleteAll(mAtlas);
}

void SpriteAtlasModel::create(const QString &fileName, const Sprite::Size &size) {
    mSpriteSize = size;
    QPixmap sprite(fileName);

    unsigned int rows = sprite.width() / mSpriteSize.width;
    unsigned int cols = sprite.height() / mSpriteSize.height;

    beginInsertRows(QModelIndex(), 0, rows * cols);
    for(unsigned int j = 0; j < cols; ++j) {
        for(unsigned int i = 0; i < rows; ++i) {
            Sprite::Offset o;
            o.x = i * mSpriteSize.width;
            o.y = j * mSpriteSize.height;

            mAtlas.push_back(
                        new Sprite(sprite.copy(o.x, o.y, mSpriteSize.width, mSpriteSize.height), o)
                        );
        }
    }
    endInsertRows();

    mAtlasSize.width = rows * mSpriteSize.width;
    mAtlasSize.height = cols * mSpriteSize.height;
}

void SpriteAtlasModel::clear() {
    beginRemoveRows(QModelIndex(), 0, mAtlas.size());
    qDeleteAll(mAtlas);
    mAtlas.clear();
    endRemoveRows();
}

int SpriteAtlasModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return mAtlas.size();
}

int SpriteAtlasModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QModelIndex SpriteAtlasModel::index(int row, int column, const QModelIndex &parent) const {
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    return createIndex(row, column, mAtlas.at(row));
}

QModelIndex SpriteAtlasModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}

QVariant SpriteAtlasModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) return QVariant();

    Sprite* s = static_cast<Sprite*>(index.internalPointer());
    if(s && (role == Qt::DecorationRole)) {
        return s->pixmap();
    }

    return QVariant();
}

Qt::ItemFlags SpriteAtlasModel::flags(const QModelIndex &index) const {
    Q_UNUSED(index)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

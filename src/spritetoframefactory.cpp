#include "spritetoframefactory.h"

SpriteToFrameFactory::SpriteToFrameFactory(const QString &frameFileName, const Frame::Options &options) :
    mPixmaps(nullptr)
{
    QPixmap sprite(frameFileName);
    unsigned int spriteWidth = sprite.width();
    unsigned int spriteHeight = sprite.height();

    mRows = spriteWidth / options.width;
    mCols = spriteHeight / options.height;

    Frame::setTotalFrames(mRows * mCols);

    mPixmaps = new QPixmap[mCols * mRows];

    for(unsigned int j = 0; j < mCols; ++j) {
        for(unsigned int i = 0; i < mRows; ++i) {
            qreal x, y;
            x = i * options.width;
            y = j * options.height;
            mPixmaps[j * mCols + i] = sprite.copy(x, y, options.width, options.height);
        }
    }
}

SpriteToFrameFactory::~SpriteToFrameFactory() {
    if(mPixmaps) {
        delete[] mPixmaps;
    }
}

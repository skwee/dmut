#ifndef SPRITETOFRAMEFACTORY_H
#define SPRITETOFRAMEFACTORY_H

#include <QPixmap>

#include "frame.h"

class SpriteToFrameFactory
{
public:
    SpriteToFrameFactory(const QString& frameFileName, const Frame::Options& frameOptions);
    ~SpriteToFrameFactory();

    unsigned int totalItems() const { return mRows * mCols; }
    const QPixmap& at(unsigned int index) const { return mPixmaps[index]; }

private:
    QPixmap* mPixmaps;
    unsigned int mRows, mCols;
};

#endif // SPRITETOFRAMEFACTORY_H

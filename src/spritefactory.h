#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include <QPixmap>

#include "frame.h"

class SpriteFactory
{
public:
    SpriteFactory(const QString& spriteFileName, const Frame::Options& options);
    ~SpriteFactory();

    unsigned int totalItems() const { return mRows * mCols; }
    const QPixmap& at(unsigned int index) const { return mPixmaps[index]; }

private:
    QPixmap* mPixmaps;
    unsigned int mRows, mCols;
};

#endif // SPRITEFACTORY_H

#include "frameset.h"

#include <QPixmap>

FrameSet::FrameSet(const QString &frameFileName, const Frame::Options &options) :
    mFrameOptions(options)
{
    QPixmap sprite(frameFileName);
    unsigned int spriteWidth = sprite.width();
    unsigned int spriteHeight = sprite.height();

    mRows = spriteWidth / mFrameOptions.width;
    mCols = spriteHeight / mFrameOptions.height;

    Frame::setTotalFrames(mRows * mCols);

    mFrames = new Frame*[mCols * mRows];

    for(unsigned int j = 0; j < mCols; ++j) {
        for(unsigned int i = 0; i < mRows; ++i) {
            qreal x, y;
            x = i * mFrameOptions.width;
            y = j * mFrameOptions.height;
            mFrames[j * mCols + i] = new Frame(sprite.copy(x, y, mFrameOptions.width, mFrameOptions.height));
        }
    }
}

FrameSet::~FrameSet() {
    if(mFrames != nullptr) {
        unsigned int total = mRows * mCols;
        for(unsigned int i = 0; i < total; ++i) {
            if(mFrames[i] != nullptr) delete mFrames[i];
        }
        delete mFrames;
    }
}

bool FrameSet::isNameUnique(const QString &name, Frame* ignoreFrame) const {
    unsigned int total = mRows * mCols;
    for(unsigned int i = 0; i < total; ++i) {
        if(mFrames[i] == ignoreFrame) continue;
        if(mFrames[i]->getName().compare(name) == 0) return false;
    }
    return true;
}

#include "frameset.h"

FrameSet::FrameSet(const QString &frameFileName, const Frame::Options &options) :
    mFrameOptions(options)
{
    QPixmap sprite(frameFileName);
    unsigned int spriteWidth = sprite.width();
    unsigned int spriteHeight = sprite.height();

    mRows = spriteWidth / mFrameOptions.width;
    mCols = spriteHeight / mFrameOptions.height;

    mFrames = new Frame*[mCols * mRows];

    for(unsigned int j = 0; j < mCols; ++j) {
        for(unsigned int i = 0; i < mRows; ++i) {
            qreal x, y;
            x = i * mFrameOptions.width;
            y = j * mFrameOptions.height;
            mFrames[j * mCols + i] = new Frame(
                        sprite.copy(x, y, mFrameOptions.width, mFrameOptions.height),
                        x, y
                        );
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

void FrameSet::addSetToScene(QGraphicsScene * const scene) {
    unsigned int total = mRows * mCols;
    for(unsigned int i = 0; i < total; ++i) mFrames[i]->addToScene(scene);
}

QSize FrameSet::getSpriteSize() const {
    QSize s;
    s.setWidth(mRows * mFrameOptions.width);
    s.setHeight(mCols * mFrameOptions.height);

    return s;
}

Frame* FrameSet::getFrameAt(const QPointF &point) const {
    unsigned int x = (static_cast<unsigned int>(point.x()) / mFrameOptions.width);
    unsigned int y = (static_cast<unsigned int>(point.y()) / mFrameOptions.height);

    if((x >= mRows) || (y >= mCols)) return  nullptr; //just in case

    return mFrames[y * mCols + x];
}

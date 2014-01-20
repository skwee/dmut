#ifndef FRAMESET_H
#define FRAMESET_H

#include "frame.h"

class FrameSet
{
public:
    FrameSet(const QString& frameFileName, const Frame::Options& options);
    ~FrameSet();

    void addSetToScene(QGraphicsScene* const scene);

    QSize getSpriteSize() const;
    const Frame::Options& getFrameOptions() const { return mFrameOptions; }

    Frame* getFrameAt(const QPointF& point) const;

private:
    Frame** mFrames;
    Frame::Options mFrameOptions;
    unsigned int mRows, mCols;
};

#endif // FRAMESET_H

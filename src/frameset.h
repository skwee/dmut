#ifndef FRAMESET_H
#define FRAMESET_H

#include "frame.h"

class FrameSet
{
public:
    FrameSet(const QString& frameFileName, const Frame::Options& options);
    ~FrameSet();

    const Frame::Options& getFrameOptions() const { return mFrameOptions; }
    unsigned int totalItems() const { return mRows * mCols; }
    Frame* frameAt(unsigned int index) const { return mFrames[index]; }

    bool isNameUnique(const QString& name, Frame* ignoreFrame = nullptr) const;

private:
    Frame** mFrames;
    Frame::Options mFrameOptions;
    unsigned int mRows, mCols;
};

#endif // FRAMESET_H

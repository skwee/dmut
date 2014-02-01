#ifndef ANIMATION_H
#define ANIMATION_H

#include <QString>

#include "frame.h"

class AnimationFrame {
public:
    typedef unsigned char FrameHold;
    static const FrameHold DEFAULT_FRAME_HOLD = 1;

    AnimationFrame(Frame* frame) : mFrame(frame), mHold(DEFAULT_FRAME_HOLD) {}

    inline const Frame* frame() const { return mFrame; }
    inline FrameHold hold() const { return mHold; }
    inline void setHold(FrameHold hold) { mHold = hold; }

private:
    Frame* mFrame;
    FrameHold mHold;
};

class Animation: public Block
{
public:
    typedef unsigned char FramesPerSecond;

    static const FramesPerSecond DEFAULT_FPS = 10;

    class Namer {
    private:
        static unsigned int sIndex;

    public:
        static QString generate();
    };

    Animation();

    void setFramesPerSecond(FramesPerSecond fps) { mFramesPerSecond = fps; }
    FramesPerSecond getFramesPerSecond() const { return mFramesPerSecond; }

private:
    FramesPerSecond mFramesPerSecond;
};

#endif // ANIMATION_H

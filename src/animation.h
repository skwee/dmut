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

class Animation
{
public:
    typedef unsigned char FramesPerSecond;

    static const FramesPerSecond DEFAULT_FPS = 10;

    class Namer {
    private:
        static unsigned int sIndex;

    public:
        static const int MAX_LENGTH = 32;

        enum class NameValidity {
            Valid,
            Empty,
            TooLong,
            Duplicate
        };

        static QString generate();
        static NameValidity validate(const QString& name);
    };

    Animation();
    ~Animation();

    void setName(const QString& name) { mName = name; }
    QString getName() const { return mName; }

    void setFramesPerSecond(FramesPerSecond fps) { mFramesPerSecond = fps; }
    FramesPerSecond getFramesPerSecond() const { return mFramesPerSecond; }

    void addFrame(Frame* frame);
    AnimationFrame* frameAt(int index) const;
    void removeFrame(int index);
    int totalFrames() const { return mFrames.size(); }

private:
    QString mName;
    FramesPerSecond mFramesPerSecond;
    QList<AnimationFrame*> mFrames;
};

#endif // ANIMATION_H

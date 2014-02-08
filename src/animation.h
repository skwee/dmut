#ifndef ANIMATION_H
#define ANIMATION_H

#include "item.h"

class Animation: public Item
{
public:
    typedef unsigned char FramesPerSecond;
    const FramesPerSecond DEFAULT_FPS = 20;

    enum class WrapMode{
        Once,
        Loop
    };

    Animation();

    inline FramesPerSecond getFPS() const { return mFps; }
    void setFPS(FramesPerSecond fps) { mFps = fps; }

    inline WrapMode getWrapMode() const { return mWrapMode; }
    void setWrapMode(WrapMode wrapMode) { mWrapMode = wrapMode; }

    int columnCount() const override;
    Qt::ItemFlags flags() const override;
    Item* getNewChild() override;

private:
    FramesPerSecond mFps;
    WrapMode mWrapMode;
};

#endif // ANIMATION_H

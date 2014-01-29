#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include "frame.h"

#include <vector>

class AnimationFrame
{
public:
    typedef std::vector<AnimationFrame> List;

    AnimationFrame(Frame::Ptr frame, unsigned int duration = 0);

    QString getName() const { return mFrame->getName(); }
    unsigned int getDuration() const { return mDuration; }
    void setDuration(unsigned int duration) { mDuration = duration; }
    void setActive(bool active) { mFrame->setActive(active); }

private:
    Frame::Ptr mFrame;
    unsigned int mDuration;
};

#endif // ANIMATIONFRAME_H

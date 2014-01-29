#include "animationframe.h"

AnimationFrame::AnimationFrame(Frame::Ptr frame, unsigned int duration) :
    mFrame(frame), mDuration(duration)
{
}

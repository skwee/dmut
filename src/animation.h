#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

#include "animationframe.h"

class Animation
{
private:
    static unsigned int sNext;

public:
    typedef std::shared_ptr<Animation> Ptr;

    Animation();

    void setName(const QString& name) { mName = name; }
    QString getName() const { return mName; }

    void addFrame(Frame::Ptr frame);

    const AnimationFrame::List* getList() const { return &mFrameList; }

private:
    QString mName;
    AnimationFrame::List mFrameList;
};

#endif // ANIMATION_H

#ifndef ANIMATION_H
#define ANIMATION_H

#include "frame.h"

class Animation
{
private:
    static unsigned int sNext;

public:
    typedef std::shared_ptr<Animation> Ptr;

    Animation();

    void setName(const QString& name) { mName = name; }
    QString getName() const { return mName; }

private:
    QString mName;
};

#endif // ANIMATION_H

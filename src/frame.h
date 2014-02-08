#ifndef FRAME_H
#define FRAME_H

#include "item.h"

class Frame: public Item
{
public:
    typedef unsigned char Duration;

    Frame();

    inline Duration getDuration() const { return mDuration; }
    inline void setDuration(Duration duration) { mDuration = duration; }

    int columnCount() const override;
    Qt::ItemFlags flags() const override;

    Item* getNewChild();

private:
    Duration mDuration;
};

#endif // FRAME_H

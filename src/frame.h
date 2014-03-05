#ifndef FRAME_H
#define FRAME_H

#include "item.h"
#include "sprite.h"

class Frame: public Item
{
public:
    typedef double Duration;

    Frame();

    inline Duration getDuration() const { return mDuration; }
    inline void setDuration(Duration duration) { mDuration = duration; }

    inline Sprite* getSprite() const { return mSprite; }

    Qt::ItemFlags flags() const override;

    Item* getNewChild() override;

    QVariant data(int column, int role) const override;
    bool setData(const QVariant& value, int column, int role) override;

    Item::Type type() override {
        return Item::Type::FRAME;
    }

private:
    Duration mDuration;
    Sprite* mSprite;
};

#endif // FRAME_H

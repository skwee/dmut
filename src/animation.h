#ifndef ANIMATION_H
#define ANIMATION_H

#include "item.h"

class Animation: public Item
{
public:
    typedef unsigned char WrapMode;
    enum {
        WrapOnce = 0,
        WrapLoop = 1
    };

    static QStringList getWrapModes() {
        QStringList wrapModes;
        wrapModes << QObject::tr("Once") << QObject::tr("Loop");
        return wrapModes;
    }

    Animation();

    inline WrapMode getWrapMode() const { return mWrapMode; }

    inline double spf() const { return 1.0f / fps(); }
    double fps() const;
    inline double length() const { return mLength; }

    Qt::ItemFlags flags() const override;
    Item* getNewChild() override;

    QVariant data(int column, int role) const override;
    bool setData(const QVariant& value, int column, int role) override;

    Item::Type type() override {
        return Item::Type::ANIMATION;
    }

private:
    WrapMode mWrapMode;
    double mLength;
};

#endif // ANIMATION_H

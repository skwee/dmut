#ifndef ROOTITEM_H
#define ROOTITEM_H

#include "item.h"

class RootItem: public Item
{
public:
    RootItem();

    Item* getNewChild() override;
    Item::Type type() override {
        return Item::Type::ROOT;
    }
};

#endif // ROOTITEM_H

#ifndef ROOTITEM_H
#define ROOTITEM_H

#include "item.h"

class RootItem: public Item
{
public:
    RootItem();

    Item* getNewChild() override;
};

#endif // ROOTITEM_H

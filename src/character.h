#ifndef CHARACTER_H
#define CHARACTER_H

#include "item.h"

class Character: public Item
{
public:
    Character(const QString& name);

    int columnCount() const override;
    Qt::ItemFlags flags() const override;
    Item* getNewChild() override;
};

#endif // CHARACTER_H

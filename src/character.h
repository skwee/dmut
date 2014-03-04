#ifndef CHARACTER_H
#define CHARACTER_H

#include "item.h"

class Character: public Item
{
public:
    Character(const QString& name);

    Qt::ItemFlags flags() const override;
    Item* getNewChild() override;

    virtual QVariant data(int column, int role) const;

    Item::Type type() override {
        return Item::Type::CHARACTER;
    }
};

#endif // CHARACTER_H

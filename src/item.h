#ifndef ITEM_H
#define ITEM_H

#include "block.h"

class Item: public ItemInterface
{
public:
    Item(Block::ptr block, Item* parent = nullptr);
    virtual ~Item();

    void add(Item* item);
    Item* at(int index) const;
    void remove(int index);
    void removeAll();
    void removeSelf();
    inline int total() const { return mChildren.size(); }

    int indexOfSelf();
    bool contains(Block::ptr block);

    QString name() const override;
    Item::RenameResult rename(const QString &name);

    QVariant display() const override;
    QVariant decoration() const override;

    inline Block::ptr block() const { return mBlock; }
    inline Item* parent() const { return mParent; }
    int row();

private:
    bool indexIsValid(int index) const;
    bool isNameUniqueAmongSiblings(const QString& name, const Item* except);

    Block::ptr mBlock;
    Item* mParent;
    QList<Item*> mChildren;
};

#endif // ITEM_H

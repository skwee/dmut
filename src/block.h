#ifndef BLOCK_H
#define BLOCK_H

#include <QSharedPointer>

#include "iteminterface.h"

class Block: public ItemInterface
{
public:
    enum class Type {
        None,
        Frame,
        Animation
    };

    typedef QSharedPointer<Block> ptr;

    Block(const QString& name, Type type);
    virtual ~Block();

    QString name() const override { return mName; }
    ItemInterface::RenameResult rename(const QString& name) override { mName = name; return RenameResult::Ok; }

    virtual QVariant display() const override;
    virtual QVariant decoration() const override;

    inline Type type() const { return mType; }

private:
    QString mName;
    Type mType;
};

#endif // BLOCK_H

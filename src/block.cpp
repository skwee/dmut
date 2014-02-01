#include "block.h"

Block::Block(const QString& name, Type type) :
    mName(name), mType(type)
{
}

Block::~Block() {
}

QVariant Block::display() const {
    return mName;
}

QVariant Block::decoration() const {
    return QVariant();
}

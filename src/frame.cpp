#include "frame.h"
#include "namer.h"

Frame::Frame() :
    Item(Namer::generateFrameName()), mDuration(1)
{}

Qt::ItemFlags Frame::flags() const {
    return Item::flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

Item* Frame::getNewChild() {
    return nullptr;
}

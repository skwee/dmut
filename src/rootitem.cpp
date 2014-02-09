#include "rootitem.h"

RootItem::RootItem():
    Item("RootItem")
{}

Item* RootItem::getNewChild() {
    return nullptr;
}

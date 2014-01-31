#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QVariant>
#include <exception>

class Item;

class ItemOptionsMismatchException: public std::exception {
public:
    ItemOptionsMismatchException(const std::string& error, const Item* who): mError(error), mWho(who) {}

    const char* what() const noexcept;

private:
    std::string mError;
    const Item* mWho;
};

class Item
{
public:
    static const int MAX_NAME_LENGTH = 32;

    enum Options {
        None = 0x00,
        CanHaveChildren = 0x01
    };

    enum class ItemType {
        Root,
        Frame,
        Animation
    };

    enum class RenameResult {
        Ok,
        Empty,
        TooLong,
        Duplicate
    };

    Item(const QString name, Item* parent = nullptr, unsigned int options = Options::CanHaveChildren, ItemType type = ItemType::Root);
    virtual ~Item();

    inline Item* parent() const { return mParent; }

    void childAdd(Item* item);
    Item* childAt(int index);
    void childRemove(int index);
    void childRemoveAll();
    inline int childCount() const { return mChildren.size(); }

    inline ItemType type() const { return mItemType; }

    int row() ;

    QString name() const { return mName; }
    RenameResult rename(const QString& newName);

    virtual QString display() const;
    virtual QVariant decoration() const;

private:
    bool isNameUniqueAmongSiblings(const QString& name, const Item* except);

    QString mName;
    Item* const mParent;
    unsigned int mOptions;
    ItemType mItemType;
    QList<Item*> mChildren;
};

#endif // ITEM_H

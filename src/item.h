#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QList>
#include <QVariant>

class Item
{
public:
    Item(const QString& name);
    virtual ~Item();

    inline QString name() const { return mName; }
    inline void rename(const QString& name) { mName = name; }

    inline Item* parent() const { return mParent; }

    int rowCount() const;
    virtual int columnCount() const;

    int rowIndex() const;

    virtual QVariant data(int role) const;
    virtual Qt::ItemFlags flags() const;

    Item* at(int index) const;
    void add(Item* item);

    virtual Item* getNewChild() = 0;

private:
    Item* mParent;
    QString mName;
    QList<Item*> mChildren;
};

#endif // ITEM_H

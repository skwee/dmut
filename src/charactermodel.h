#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include <QAbstractItemModel>

#include "rootitem.h"
#include "character.h"

class CharacterModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CharacterModel(Character* character, QObject *parent = 0);
    ~CharacterModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    RootItem* root() const { return mRoot; }

public slots:
    void addItemTo(const QModelIndex& index);
    void removeItem(const QModelIndex& index);

signals:
    void itemAdded(const QModelIndex& toIndex, Item* parent, Item* child);
    void changed();

private:
    RootItem* mRoot;
};

#endif // CHARACTERMODEL_H

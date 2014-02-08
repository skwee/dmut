#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include <QAbstractItemModel>

#include "character.h"

class CharacterModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CharacterModel(Character* root, QObject *parent = 0);
    ~CharacterModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void itemAdded(Item* parent, Item* child);

public slots:
    void addItemTo(const QModelIndex& index);

private:
    Character* mRoot;
};

#endif // CHARACTERMODEL_H

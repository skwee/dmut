#ifndef CHARACTERDOCUMENT_H
#define CHARACTERDOCUMENT_H

#include <QWidget>

#include "character.h"
#include "charactermodel.h"

class CharacterDocument: public QObject
{
    Q_OBJECT
public:
    static CharacterDocument* create(QWidget* parent = 0);
    ~CharacterDocument();

    CharacterModel* model() const { return mModel; }

signals:
    void onAddItemAction(const QModelIndex& index);
    void onRemoveItemAction(const QModelIndex& index);
    void onItemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected);

private:
    CharacterDocument(const QString& name);

    Character* mCharacter;
    CharacterModel* mModel;
};

#endif // CHARACTERDOCUMENT_H

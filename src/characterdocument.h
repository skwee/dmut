#ifndef CHARACTERDOCUMENT_H
#define CHARACTERDOCUMENT_H

#include <QWidget>

#include "character.h"
#include "charactermodel.h"
#include "sprite.h"

class CharacterDocument: public QObject
{
    Q_OBJECT
public:
    static CharacterDocument* create(QWidget* parent = 0);
    ~CharacterDocument();

    inline CharacterModel* model() const { return mModel; }
    inline Sprite::Size frameSize() const { return mFrameSize; }

signals:
    void onAddItemAction(const QModelIndex& index);
    void onRemoveItemAction(const QModelIndex& index);
    void onItemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected);

private:
    CharacterDocument(const QString& name, const Sprite::Size& frameSize);

    Sprite::Size mFrameSize;
    Character* mCharacter;
    CharacterModel* mModel;
};

#endif // CHARACTERDOCUMENT_H

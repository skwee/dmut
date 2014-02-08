#ifndef CHARACTERDOCUMENT_H
#define CHARACTERDOCUMENT_H

#include <QWidget>

#include "character.h"
#include "charactermodel.h"

class CharacterDocument
{
public:
    static CharacterDocument* create(QWidget* parent = 0);
    ~CharacterDocument();

    CharacterModel* model() const { return mModel; }

private:
    CharacterDocument(const QString& name);

    Character* mCharacter;
    CharacterModel* mModel;
};

#endif // CHARACTERDOCUMENT_H

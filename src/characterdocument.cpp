#include "characterdocument.h"
#include "newcharacterdialog.h"
#include "namer.h"

CharacterDocument* CharacterDocument::create(QWidget* parent) {
    Namer::reset();

    NewCharacterDialog nc(Namer::generateCharacterName(), parent);
    if(nc.exec() == QDialog::Accepted) {
        return new CharacterDocument(nc.getCharacterName());
    }
    return nullptr;
}

CharacterDocument::CharacterDocument(const QString &name) :
    mCharacter(nullptr), mModel(nullptr)
{
    mCharacter = new Character(name);
    mModel = new CharacterModel(mCharacter);

    QObject::connect(
                this, SIGNAL(onAddItemAction(QModelIndex)),
                mModel, SLOT(addItemTo(QModelIndex))
                );

    QObject::connect(
                this, SIGNAL(onRemoveItemAction(QModelIndex)),
                mModel, SLOT(removeItem(QModelIndex))
                );
}

CharacterDocument::~CharacterDocument() {
    if(mModel) delete mModel;
}

#include "characterdetailseditor.h"
#include "ui_characterdetailseditor.h"

CharacterDetailsEditor::CharacterDetailsEditor(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::CharacterDetailsEditor)
{
    mUi->setupUi(this);
}

CharacterDetailsEditor::~CharacterDetailsEditor()
{
    delete mUi;
}

QDataWidgetMapper* CharacterDetailsEditor::createMapper(CharacterModel* model) {
    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(mUi->nameEdit, 0);

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mapper;
}

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
    mapper->addMapping(mUi->nameEdit, Item::ColumnName);

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mapper;
}

void CharacterDetailsEditor::clear() {
    mUi->nameEdit->setText("");
}

#include "framedetailseditor.h"
#include "ui_framedetailseditor.h"

FrameDetailsEditor::FrameDetailsEditor(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::FrameDetailsEditor)
{
    mUi->setupUi(this);
}

FrameDetailsEditor::~FrameDetailsEditor()
{
    delete mUi;
}

QDataWidgetMapper* FrameDetailsEditor::createMapper(CharacterModel* model) {
    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(mUi->nameEdit, 0);

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mapper;
}

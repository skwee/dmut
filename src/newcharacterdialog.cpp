#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(const QString& characterName, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::NewCharacterDialog)
{
    mUi->setupUi(this);
    mUi->nameLineEdit->setText(characterName);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete mUi;
}

QString NewCharacterDialog::getSpriteName() const {
    return mUi->nameLineEdit->text();
}

Sprite::Size NewCharacterDialog::getSpriteSize() const {
    Sprite::Size s;
    s.width = mUi->frameSizeWidthSpinBox->value();
    s.height = mUi->frameSizeHeightSpinBox->value();

    return s;
}

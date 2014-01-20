#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(QWidget *parent, const QString &characterName) :
    QDialog(parent),
    mUi(new Ui::NewCharacterDialog)
{
    mUi->setupUi(this);
    mUi->characterNameEdit->setText(characterName);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete mUi;
}

Frame::Options NewCharacterDialog::getCharacterFrameOptions() const {
    Frame::Options o;

    o.width = mUi->frameWidthBox->value();
    o.height = mUi->frameHeightBox->value();

    return o;
}

QString NewCharacterDialog::getCharacterName() const {
    return mUi->characterNameEdit->text();
}

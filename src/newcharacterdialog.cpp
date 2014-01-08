#include "newcharacterdialog.h"
#include "ui_newcharacterdialog.h"

NewCharacterDialog::NewCharacterDialog(QWidget *parent, const QString &characterName) :
    QDialog(parent),
    ui(new Ui::NewCharacterDialog)
{
    ui->setupUi(this);
    ui->characterNameEdit->setText(characterName);
}

NewCharacterDialog::~NewCharacterDialog()
{
    delete ui;
}

NewCharacterDialog::NewCharacterCreationData NewCharacterDialog::getCharacterCreationData() const {
    NewCharacterCreationData nccd;

    nccd.name = ui->characterNameEdit->text();
    nccd.frame.w = ui->frameWidthBox->value();
    nccd.frame.h = ui->frameHeightBox->value();
    nccd.margin.x = ui->marginXBox->value();
    nccd.margin.y = ui->marginYBox->value();
    nccd.spacing.x = ui->xSpacingBox->value();
    nccd.spacing.y = ui->ySpacingBox->value();

    return nccd;
}

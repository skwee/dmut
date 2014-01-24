#include "textinputdialog.h"
#include "ui_textinputdialog.h"

TextInputDialog::TextInputDialog(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::TextInputDialog)
{
    mUi->setupUi(this);
}

TextInputDialog::~TextInputDialog()
{
    delete mUi;
}

void TextInputDialog::setText(const QString &text) {
    mUi->textField->setText(text);
}

QString TextInputDialog::getText() const {
    return mUi->textField->text();
}

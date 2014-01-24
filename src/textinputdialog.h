#ifndef TEXTINPUTDIALOG_H
#define TEXTINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class TextInputDialog;
}

class TextInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextInputDialog(QWidget *parent = 0);
    ~TextInputDialog();

    void setText(const QString& text);
    QString getText() const;

private:
    Ui::TextInputDialog *mUi;
};

#endif // TEXTINPUTDIALOG_H

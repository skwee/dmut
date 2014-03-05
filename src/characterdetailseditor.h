#ifndef CHARACTERDETAILSEDITOR_H
#define CHARACTERDETAILSEDITOR_H

#include <QFrame>
#include <QDataWidgetMapper>

#include "charactermodel.h"

namespace Ui {
class CharacterDetailsEditor;
}

class CharacterDetailsEditor : public QFrame
{
    Q_OBJECT

public:
    explicit CharacterDetailsEditor(QWidget *parent = 0);
    ~CharacterDetailsEditor();

    QDataWidgetMapper* createMapper(CharacterModel* model);

    void clear();

private:
    Ui::CharacterDetailsEditor *mUi;
};

#endif // CHARACTERDETAILSEDITOR_H

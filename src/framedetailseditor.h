#ifndef FRAMEDETAILSEDITOR_H
#define FRAMEDETAILSEDITOR_H

#include <QFrame>
#include <QDataWidgetMapper>

#include "charactermodel.h"

namespace Ui {
class FrameDetailsEditor;
}

class FrameDetailsEditor : public QFrame
{
    Q_OBJECT

public:
    explicit FrameDetailsEditor(QWidget *parent = 0);
    ~FrameDetailsEditor();

    QDataWidgetMapper* createMapper(CharacterModel* model);

private:
    Ui::FrameDetailsEditor *mUi;
};

#endif // FRAMEDETAILSEDITOR_H

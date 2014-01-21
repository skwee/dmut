#include "animationeditor.h"
#include "ui_animationeditor.h"

AnimationEditor::AnimationEditor(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::AnimationEditor)
{
    mUi->setupUi(this);
}

AnimationEditor::~AnimationEditor()
{
    delete mUi;
}

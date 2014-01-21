#ifndef ANIMATIONEDITOR_H
#define ANIMATIONEDITOR_H

#include <QWidget>

namespace Ui {
class AnimationEditor;
}

class AnimationEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationEditor(QWidget *parent = 0);
    ~AnimationEditor();

private:
    Ui::AnimationEditor *mUi;
};

#endif // ANIMATIONEDITOR_H

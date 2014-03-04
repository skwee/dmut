#ifndef FRAMEDETAILSEDITOR_H
#define FRAMEDETAILSEDITOR_H

#include <QFrame>
#include <QDataWidgetMapper>

#include "charactermodel.h"
#include "spriteatlasdialog.h"

namespace Ui {
class FrameDetailsEditor;
}

class FrameDetailsEditor : public QFrame
{
    Q_OBJECT

public:
    explicit FrameDetailsEditor(QWidget *parent = 0);
    ~FrameDetailsEditor();

    QDataWidgetMapper* createMapper(CharacterModel* model, const Sprite::Size& frameSize);

private slots:
    void on_spriteSelectButton_clicked();

private:
    Ui::FrameDetailsEditor *mUi;
    SpriteAtlasDialog* mSpriteAtlas;
    Sprite::Size mFrameSize;
};

#endif // FRAMEDETAILSEDITOR_H

#ifndef SPRITEATLASWIDGET_H
#define SPRITEATLASWIDGET_H

#include <QWidget>

#include "spriteatlasmodel.h"

namespace Ui {
class SpriteAtlasWidget;
}

class SpriteAtlasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteAtlasWidget(QWidget *parent = 0);
    ~SpriteAtlasWidget();

    void setAtlas(const QString& fileName, const Sprite::Size& size);

private:
    Ui::SpriteAtlasWidget *mUi;
    SpriteAtlasModel* mModel;
};

#endif // SPRITEATLASWIDGET_H

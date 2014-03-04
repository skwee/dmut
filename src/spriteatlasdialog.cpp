#include "spriteatlasdialog.h"
#include "ui_spriteatlasdialog.h"

SpriteAtlasDialog::SpriteAtlasDialog(const QString &fileName, const Sprite::Size &size, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::SpriteAtlasDialog)
{
    mUi->setupUi(this);

    //@TODO create custom scene with "selected" event
    //connect scene to view

    mScene = new QGraphicsScene();

    SpriteAtlasModel atlas(fileName, size);
    for(Sprite* s : atlas.items()) {
        mScene->addItem(s);
    }

    mUi->gview->setScene(mScene);
}

SpriteAtlasDialog::~SpriteAtlasDialog()
{
    if(mScene) delete mScene;
    delete mUi;
}

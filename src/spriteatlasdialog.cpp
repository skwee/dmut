#include "spriteatlasdialog.h"
#include "ui_spriteatlasdialog.h"

SpriteAtlasDialog::SpriteAtlasDialog(const QString &fileName, const Sprite::Size &size, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::SpriteAtlasDialog)
{
    mUi->setupUi(this);

    mScene = new SpriteAtlasScene();

    QObject::connect(
                mScene, SIGNAL(onItemSelected()),
                this, SLOT(itemSelected())
                );

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

void SpriteAtlasDialog::itemSelected() {
    Sprite* s = mScene->selectedItem();
    if(s) {
        emit onSpriteSelected(s);
        done(1);
    }
}

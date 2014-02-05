#include "spriteatlaswidget.h"
#include "ui_spriteatlaswidget.h"

SpriteAtlasWidget::SpriteAtlasWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::SpriteAtlasWidget), mModel(nullptr)
{
    mUi->setupUi(this);

    mModel = new SpriteAtlasModel(this);
    mUi->spriteAtlasList->setModel(mModel);
}

SpriteAtlasWidget::~SpriteAtlasWidget()
{
    if(mModel) delete mModel;
    delete mUi;
}

void SpriteAtlasWidget::setAtlas(const QString &fileName, const Sprite::Size &size) {
    mModel->clear();
    mModel->create(fileName, size);
    mUi->spriteAtlasList->setGridSize(QSize(size.width, size.height));
}

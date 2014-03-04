#include "framedetailseditor.h"
#include "ui_framedetailseditor.h"

#include <QFileDialog>
#include <QMessageBox>

FrameDetailsEditor::FrameDetailsEditor(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::FrameDetailsEditor), mSpriteAtlas(nullptr)
{
    mUi->setupUi(this);
}

FrameDetailsEditor::~FrameDetailsEditor()
{
    if(mSpriteAtlas) delete mSpriteAtlas;
    delete mUi;
}

QDataWidgetMapper* FrameDetailsEditor::createMapper(CharacterModel* model, const Sprite::Size& frameSize) {
    mFrameSize = frameSize;

    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(mUi->nameEdit, Item::ColumnName);
    mapper->addMapping(mUi->durationEdit, Item::ColumnFrameDuration);

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mapper;
}

void FrameDetailsEditor::on_spriteSelectButton_clicked() {
    if(mSpriteAtlas == nullptr) {
        QString fileName = QFileDialog::getOpenFileName(
                    this,
                    tr("Select Sprite Atlas"),
                    QDir::homePath(),
                    QString("Images (*.png *.jpg)")
                    );

        QFile file(fileName);
        if(file.exists()) {
            mUi->spriteFileLabel->setText(file.fileName());
            mSpriteAtlas = new SpriteAtlasDialog(file.fileName(), mFrameSize, mUi->spriteSelectButton);

//            mSpriteAtlas->setGeometry(QRect(
//                                          mUi->spriteSelectButton->mapToGlobal(QPoint(0, mUi->spriteSelectButton->height())),
//                                          mSpriteAtlas->size()
//                                          ));
        } else {
            QMessageBox::warning(this, tr("Select Sprite Atlas"), tr("Please select a valid sprite atlas image to attach sprites to frames"));
        }
    }

    if(mSpriteAtlas) {
        mSpriteAtlas->show();
    }
}

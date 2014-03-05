#include "framedetailseditor.h"
#include "ui_framedetailseditor.h"

#include <QFileDialog>
#include <QMessageBox>

FrameSpriteIconDelegate::FrameSpriteIconDelegate(QPushButton *button, QObject *parent):
    QItemDelegate(parent), mSpriteSelectButton(button)
{}

void FrameSpriteIconDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if(editor == mSpriteSelectButton) {
        Sprite* sprite = index.data().value<Sprite*>();
        if(sprite == nullptr) {
            mSpriteSelectButton->setIcon(QIcon());
            mSpriteSelectButton->setText("...");
        } else {
            mSpriteSelectButton->setText("");
            mSpriteSelectButton->setIcon(QIcon(sprite->pixmap()));
        }
        return;
    }
    QItemDelegate::setEditorData(editor, index);
}

void FrameSpriteIconDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QItemDelegate::setModelData(editor, model, index);
}


FrameDetailsEditor::FrameDetailsEditor(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::FrameDetailsEditor), mSpriteAtlas(nullptr), mMapper(nullptr)
{
    mUi->setupUi(this);
}

FrameDetailsEditor::~FrameDetailsEditor()
{
    mMapper = nullptr;
    if(mSpriteAtlas) delete mSpriteAtlas;
    delete mUi;
}

QDataWidgetMapper* FrameDetailsEditor::createMapper(CharacterModel* model, const Sprite::Size& frameSize) {
    if(mMapper) return mMapper;

    mFrameSize = frameSize;

    mMapper = new QDataWidgetMapper(this);
    mMapper->setModel(model);
    mMapper->addMapping(mUi->nameEdit, Item::ColumnName);
    mMapper->addMapping(mUi->durationEdit, Item::ColumnFrameDuration);
    mMapper->addMapping(mUi->spriteSelectButton, Item::ColumnFrameSpriteIcon);
    mUi->spriteSelectButton->setIconSize(QSize(frameSize.width, frameSize.height));
    mMapper->setItemDelegate(new FrameSpriteIconDelegate(mUi->spriteSelectButton, this));

    QObject::connect(
                mUi->durationEdit, SIGNAL(valueChanged(double)),
                this, SLOT(submitChanges())
                );

    mMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mMapper;
}

void FrameDetailsEditor::clear() {
    mUi->nameEdit->setText("");
    mUi->durationEdit->setValue(1);
    mUi->spriteSelectButton->setIcon(QIcon());
    mUi->spriteSelectButton->setText("...");
}

void FrameDetailsEditor::submitChanges() {
    if(mMapper) mMapper->submit();
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

            QObject::connect(
                        mSpriteAtlas, SIGNAL(onSpriteSelected(Sprite*)),
                        this, SIGNAL(onSpriteSelected(Sprite*))
                        );

            QObject::connect(
                        mSpriteAtlas, SIGNAL(onSpriteSelected(Sprite*)),
                        this, SLOT(submitChanges())
                        );
        } else {
            QMessageBox::warning(this, tr("Select Sprite Atlas"), tr("Please select a valid sprite atlas image to attach sprites to frames"));
        }
    }

    if(mSpriteAtlas) {
        mSpriteAtlas->open();
    }
}

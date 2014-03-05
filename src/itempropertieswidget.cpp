#include "itempropertieswidget.h"
#include "ui_itempropertieswidget.h"

#include "item.h"

ItemPropertiesWidget::ItemPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::ItemPropertiesWidget),
    mCharacterMapper(nullptr), mAnimationMapper(nullptr), mFrameMapper(nullptr),
    mSelectedItem(QModelIndex())
{
    mUi->setupUi(this);

    mUi->characterDataFrame->setDisabled(true);
    mUi->animationDataFrame->setDisabled(true);
    mUi->frameDataFrame->setDisabled(true);
}

ItemPropertiesWidget::~ItemPropertiesWidget()
{
    finishSession();
    delete mUi;
}

void ItemPropertiesWidget::startSession(CharacterDocument *document) {
    finishSession();

    mCharacterMapper = mUi->characterDataFrame->createMapper(document->model());
    mAnimationMapper = mUi->animationDataFrame->createMapper(document->model());
    mFrameMapper = mUi->frameDataFrame->createMapper(document->model(), document->frameSize());

    QObject::connect(
                mUi->frameDataFrame, SIGNAL(onSpriteSelected(Sprite*)),
                this, SLOT(spriteSelected(Sprite*))
                );
}

void ItemPropertiesWidget::finishSession() {
    if(mCharacterMapper) {
        delete mCharacterMapper;
        mCharacterMapper = nullptr;
    }

    if(mAnimationMapper) {
        delete mAnimationMapper;
        mAnimationMapper = nullptr;
    }

    if(mFrameMapper) {
        delete mFrameMapper;
        mFrameMapper = nullptr;
    }
}

void ItemPropertiesWidget::itemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected) {
    setSelectedItem(selected);
}

void ItemPropertiesWidget::setSelectedItem(const QModelIndex& index) {
    if(!index.isValid()) return;

    mSelectedItem = index;

    Item* item = static_cast<Item*>(index.internalPointer());

    mUi->characterDataFrame->setDisabled(true);
    mUi->animationDataFrame->setDisabled(true);
    mUi->frameDataFrame->setDisabled(true);

    switch(item->type()) {
    case Item::Type::CHARACTER:
        mUi->characterDataFrame->setDisabled(false);

//        mUi->characterDataFrame->clear();
        mUi->animationDataFrame->clear();
        mUi->frameDataFrame->clear();

        mCharacterMapper->setCurrentModelIndex(index);
        break;

    case Item::Type::ANIMATION:
        mUi->characterDataFrame->setDisabled(false);
        mUi->animationDataFrame->setDisabled(false);

        mUi->frameDataFrame->clear();

        mCharacterMapper->setCurrentModelIndex(index.parent());

        mAnimationMapper->setRootIndex(index.parent());
        mAnimationMapper->setCurrentModelIndex(index);
        break;

    case Item::Type::FRAME:
        mUi->characterDataFrame->setDisabled(false);
        mUi->animationDataFrame->setDisabled(false);
        mUi->frameDataFrame->setDisabled(false);

        mCharacterMapper->setCurrentModelIndex(index.parent().parent());

        mAnimationMapper->setRootIndex(index.parent().parent());
        mAnimationMapper->setCurrentModelIndex(index.parent());

        mFrameMapper->setRootIndex(index.parent());
        mFrameMapper->setCurrentModelIndex(index);
        break;
    }
}

void ItemPropertiesWidget::spriteSelected(Sprite *sprite) {
    if(mSelectedItem.isValid()) {
        Item* item = static_cast<Item*>(mSelectedItem.internalPointer());
        if(item->type() == Item::Type::FRAME) {
            item->setData(QVariant::fromValue<Sprite*>(sprite), Item::ColumnFrameSprite, Qt::EditRole);
        }
    }
}

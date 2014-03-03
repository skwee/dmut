#include "itempropertieswidget.h"
#include "ui_itempropertieswidget.h"

#include "item.h"

ItemPropertiesWidget::ItemPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::ItemPropertiesWidget),
    mCharacterMapper(nullptr), mAnimationMapper(nullptr), mFrameMapper(nullptr)
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
    mFrameMapper = mUi->frameDataFrame->createMapper(document->model());
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
    if(!selected.isValid()) return;

    Item* item = static_cast<Item*>(selected.internalPointer());

    mUi->characterDataFrame->setDisabled(true);
    mUi->animationDataFrame->setDisabled(true);
    mUi->frameDataFrame->setDisabled(true);

    switch(item->type()) {
    case Item::Type::CHARACTER:
        mUi->characterDataFrame->setDisabled(false);

        mCharacterMapper->setCurrentModelIndex(selected);
        break;

    case Item::Type::ANIMATION:
        mUi->characterDataFrame->setDisabled(false);
        mUi->animationDataFrame->setDisabled(false);

        mCharacterMapper->setCurrentModelIndex(selected.parent());

        mAnimationMapper->setRootIndex(selected.parent());
        mAnimationMapper->setCurrentModelIndex(selected);
        break;

    case Item::Type::FRAME:
        mUi->characterDataFrame->setDisabled(false);
        mUi->animationDataFrame->setDisabled(false);
        mUi->frameDataFrame->setDisabled(false);

        mCharacterMapper->setCurrentModelIndex(selected.parent().parent());

        mAnimationMapper->setRootIndex(selected.parent().parent());
        mAnimationMapper->setCurrentModelIndex(selected.parent());

        mFrameMapper->setRootIndex(selected.parent());
        mFrameMapper->setCurrentModelIndex(selected);
        break;
    }
}

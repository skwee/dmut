#include "animationdetailseditor.h"
#include "ui_animationdetailseditor.h"

#include "animation.h"

#include <QMetaProperty>

AnimationWrapModeDelegate::AnimationWrapModeDelegate(QWidget* wrapModeSelector, QObject *parent) :
    QItemDelegate(parent), mWrapModeSelector(wrapModeSelector)
{}

void AnimationWrapModeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if(editor == mWrapModeSelector) {
        QComboBox* cb = static_cast<QComboBox*>(editor);
        cb->setCurrentIndex(index.data().toInt());
        return;
    }
    QItemDelegate::setEditorData(editor, index);
}

void AnimationWrapModeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if(editor == mWrapModeSelector) {
        QComboBox* cb = static_cast<QComboBox*>(editor);
        model->setData(index, cb->currentIndex());
        return;
    }
    QItemDelegate::setModelData(editor, model, index);
}


AnimationDetailsEditor::AnimationDetailsEditor(QWidget *parent) :
    QFrame(parent),
    mUi(new Ui::AnimationDetailsEditor), mWrapModesModel(nullptr), mMapper(nullptr)
{
    mUi->setupUi(this);
    mWrapModesModel = new QStringListModel(Animation::getWrapModes(), this);
    mUi->wrapModeCombo->setModel(mWrapModesModel);
}

AnimationDetailsEditor::~AnimationDetailsEditor()
{
    mMapper = nullptr;
    if(mWrapModesModel) {
        delete mWrapModesModel;
        mWrapModesModel = nullptr;
    }
    delete mUi;
}

QDataWidgetMapper* AnimationDetailsEditor::createMapper(CharacterModel* model) {
    if(mMapper) return mMapper;

    mMapper = new QDataWidgetMapper(this);
    mMapper->setModel(model);
    mMapper->addMapping(mUi->nameEdit, Item::ColumnName);
    mMapper->addMapping(mUi->fpsEdit, Item::ColumnAnimationFps);
    mMapper->addMapping(mUi->wrapModeCombo, Item::ColumnAnimationWrapMode);
    mMapper->addMapping(mUi->animationLenEdit, Item::ColumnAnimationLength);
    mMapper->setItemDelegate(new AnimationWrapModeDelegate(mUi->wrapModeCombo, this));

    QObject::connect(
                mUi->animationLenEdit, SIGNAL(valueChanged(double)),
                this, SLOT(submitChanges())
                );

    QObject::connect(
                mUi->wrapModeCombo, SIGNAL(currentIndexChanged(int)),
                this, SLOT(submitChanges())
                );

    mMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mMapper;
}

void AnimationDetailsEditor::clear() {
    mUi->nameEdit->setText("");
    mUi->fpsEdit->setValue(0.0);
    mUi->wrapModeCombo->setCurrentIndex(Animation::WrapOnce);
    mUi->animationLenEdit->setValue(0.0);
    mUi->animationLenEdit->setDisabled(false);
    mUi->fpsEdit->setDisabled(false);
}

void AnimationDetailsEditor::disableFrameRelatedFields(bool disable) {
    mUi->animationLenEdit->setDisabled(disable);
    mUi->fpsEdit->setDisabled(disable);
}

void AnimationDetailsEditor::submitChanges() {
    if(mMapper) mMapper->submit();
}

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
    mUi(new Ui::AnimationDetailsEditor), mWrapModesModel(nullptr)
{
    mUi->setupUi(this);
    mWrapModesModel = new QStringListModel(Animation::getWrapModes(), this);
    mUi->wrapModeCombo->setModel(mWrapModesModel);
}

AnimationDetailsEditor::~AnimationDetailsEditor()
{
    if(mWrapModesModel) {
        delete mWrapModesModel;
        mWrapModesModel = nullptr;
    }
    delete mUi;
}

QDataWidgetMapper* AnimationDetailsEditor::createMapper(CharacterModel* model) {
    QDataWidgetMapper* mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(mUi->nameEdit, Item::ColumnName);
    mapper->addMapping(mUi->fpsEdit, Item::ColumnAnimationFps);
    mapper->addMapping(mUi->wrapModeCombo, Item::ColumnAnimationWrapMode);
    mapper->addMapping(mUi->animationLenEdit, Item::ColumnAnimationLength);
    mapper->setItemDelegate(new AnimationWrapModeDelegate(mUi->wrapModeCombo, this));

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    return mapper;
}

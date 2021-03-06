#ifndef ANIMATIONDETAILSEDITOR_H
#define ANIMATIONDETAILSEDITOR_H

#include <QFrame>
#include <QDataWidgetMapper>
#include <QStringListModel>
#include <QItemDelegate>
#include <QObject>

#include "charactermodel.h"

namespace Ui {
class AnimationDetailsEditor;
}

class AnimationWrapModeDelegate: public QItemDelegate {
    Q_OBJECT
public:
    AnimationWrapModeDelegate(QWidget* wrapModeSelector, QObject *parent);

    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

private:
    QWidget* mWrapModeSelector;
};

class AnimationDetailsEditor : public QFrame
{
    Q_OBJECT

public:
    explicit AnimationDetailsEditor(QWidget *parent = 0);
    ~AnimationDetailsEditor();

    QDataWidgetMapper* createMapper(CharacterModel* model);

    void clear();
    void disableFrameRelatedFields(bool disable);

private slots:
    void submitChanges();

private:
    Ui::AnimationDetailsEditor *mUi;
    QStringListModel* mWrapModesModel;
    QDataWidgetMapper* mMapper;
};

#endif // ANIMATIONDETAILSEDITOR_H

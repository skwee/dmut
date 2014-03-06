#ifndef FRAMEDETAILSEDITOR_H
#define FRAMEDETAILSEDITOR_H

#include <QFrame>
#include <QDataWidgetMapper>
#include <QItemDelegate>

#include "charactermodel.h"
#include "spriteatlasdialog.h"

namespace Ui {
class FrameDetailsEditor;
}

class FrameSpriteIconDelegate: public QItemDelegate {
    Q_OBJECT
public:
    FrameSpriteIconDelegate(QPushButton* button, QObject* parent);

    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;

private:
    QPushButton* mSpriteSelectButton;
};

class FrameDetailsEditor : public QFrame
{
    Q_OBJECT

public:
    explicit FrameDetailsEditor(QWidget *parent = 0);
    ~FrameDetailsEditor();

    QDataWidgetMapper* createMapper(CharacterModel* model, const Sprite::Size& frameSize);

    void clear();

signals:
    void onSpriteSelected(Sprite* sprite);
    void onSpriteAtlasOpened(const QString& name);

private slots:
    void submitChanges();
    void on_spriteSelectButton_clicked();

private:
    Ui::FrameDetailsEditor *mUi;
    SpriteAtlasDialog* mSpriteAtlas;
    Sprite::Size mFrameSize;
    QDataWidgetMapper* mMapper;
};

#endif // FRAMEDETAILSEDITOR_H

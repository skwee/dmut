#ifndef CHARACTERHIERARCHYWIDGET_H
#define CHARACTERHIERARCHYWIDGET_H

#include <QWidget>

#include "characterdocument.h"

namespace Ui {
class CharacterHierarchyWidget;
}

class CharacterHierarchyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterHierarchyWidget(QWidget *parent = 0);
    ~CharacterHierarchyWidget();

    void finishSession();
    void startSession(CharacterDocument* document);

signals:
    void onAddItemAction(const QModelIndex& index);

private slots:
    void onAddNewItem();

private:
    Ui::CharacterHierarchyWidget *mUi;
    CharacterDocument* mDocument;
    QAction* mAddNewItemAction;
};

#endif // CHARACTERHIERARCHYWIDGET_H

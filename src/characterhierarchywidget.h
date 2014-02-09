#ifndef CHARACTERHIERARCHYWIDGET_H
#define CHARACTERHIERARCHYWIDGET_H

#include <QWidget>
#include <QItemSelection>

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

private slots:
    void onAddNewItem();
    void onRemoveItem();
    void onItemAdded(const QModelIndex& toIndex, Item* parent, Item* child);
    void onSelectionChanged(const QItemSelection& current, const QItemSelection& previous);

private:
    QModelIndex currentSelectedIndex() const;

private:
    Ui::CharacterHierarchyWidget *mUi;
    CharacterDocument* mDocument;
    QAction* mAddNewItemAction;
    QAction* mRemoveItemAction;
};

#endif // CHARACTERHIERARCHYWIDGET_H

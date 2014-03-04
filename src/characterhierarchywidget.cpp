#include "characterhierarchywidget.h"
#include "ui_characterhierarchywidget.h"

CharacterHierarchyWidget::CharacterHierarchyWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::CharacterHierarchyWidget),
    mDocument(nullptr),
    mAddNewItemAction(nullptr),
    mRemoveItemAction(nullptr)
{
    mUi->setupUi(this);
    setDisabled(true);
    setFocusPolicy(Qt::ClickFocus);

    mUi->tree->setHeaderHidden(true);

    mAddNewItemAction = new QAction(this);
    mAddNewItemAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A));
    mAddNewItemAction->setEnabled(false);

    mRemoveItemAction = new QAction(this);
    mRemoveItemAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D));
    mRemoveItemAction->setEnabled(false);

    addAction(mAddNewItemAction);
    addAction(mRemoveItemAction);

    QObject::connect(
                mAddNewItemAction, SIGNAL(triggered()),
                this, SLOT(onAddNewItem())
                );

    QObject::connect(
                mRemoveItemAction, SIGNAL(triggered()),
                this, SLOT(onRemoveItem())
                );
}

CharacterHierarchyWidget::~CharacterHierarchyWidget()
{
    if(mAddNewItemAction) delete mAddNewItemAction;
    delete mUi;
}

void CharacterHierarchyWidget::finishSession() {
    mAddNewItemAction->setEnabled(false);
    setDisabled(true);
    mUi->tree->setModel(nullptr);
    mDocument = nullptr;
}

void CharacterHierarchyWidget::startSession(CharacterDocument *document) {
    mDocument = document;

    QObject::connect(
                mDocument->model(), SIGNAL(itemAdded(QModelIndex,Item*,Item*)),
                this, SLOT(onItemAdded(QModelIndex,Item*,Item*))
                );

    mUi->tree->setModel(mDocument->model());
    setDisabled(false);
    mAddNewItemAction->setEnabled(true);
    mRemoveItemAction->setEnabled(true);

    QObject::connect(
                mUi->tree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(onSelectionChanged(QItemSelection,QItemSelection))
                );

    for(int c = 1; c <= Item::_ColumnTotal; ++c)
        mUi->tree->hideColumn(c);
}


void CharacterHierarchyWidget::onAddNewItem() {
    if(!mDocument) return;
    emit mDocument->onAddItemAction(currentSelectedIndex());
}

void CharacterHierarchyWidget::onRemoveItem() {
    if(!mDocument) return;
    emit mDocument->onRemoveItemAction(currentSelectedIndex());
}

void CharacterHierarchyWidget::onItemAdded(const QModelIndex &toIndex, Item *parent, Item *child) {
    mUi->tree->expand(toIndex);
}

void CharacterHierarchyWidget::onSelectionChanged(const QItemSelection &current, const QItemSelection &previous) {
    if(!mDocument) return;

    QModelIndex selected = QModelIndex();
    QModelIndex deselected = QModelIndex();

    if(previous.indexes().size() > 0)
        deselected = previous.indexes().first();

    if(current.indexes().size() > 0)
        selected = current.indexes().first();

    emit mDocument->onItemSelectionChanged(selected, deselected);
}

QModelIndex CharacterHierarchyWidget::currentSelectedIndex() const {
    QModelIndex index = QModelIndex();
    QModelIndexList indexes = mUi->tree->selectionModel()->selectedIndexes();
    if(indexes.size() > 0)
        index = indexes.first();
    return index;
}

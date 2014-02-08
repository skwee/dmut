#include "characterhierarchywidget.h"
#include "ui_characterhierarchywidget.h"

CharacterHierarchyWidget::CharacterHierarchyWidget(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::CharacterHierarchyWidget),
    mDocument(nullptr),
    mAddNewItemAction(nullptr)
{
    mUi->setupUi(this);
    setDisabled(true);
    setFocusPolicy(Qt::ClickFocus);

    mUi->tree->setHeaderHidden(true);

    mAddNewItemAction = new QAction(this);
    mAddNewItemAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A));
    mAddNewItemAction->setEnabled(false);

    addAction(mAddNewItemAction);

    QObject::connect(
                mAddNewItemAction, SIGNAL(triggered()),
                this, SLOT(onAddNewItem())
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
                this, SIGNAL(onAddItemAction(QModelIndex)),
                mDocument->model(), SLOT(addItemTo(QModelIndex))
                );

    mUi->tree->setModel(document->model());
    setDisabled(false);
    mAddNewItemAction->setEnabled(true);
}


void CharacterHierarchyWidget::onAddNewItem()
{
    if(!mDocument) return;
    QItemSelectionModel* sm = mUi->tree->selectionModel();

    QModelIndex index = QModelIndex();
    if(sm->selection().indexes().size() > 0)
        index = sm->selection().indexes().first();

    emit onAddItemAction(index);
}

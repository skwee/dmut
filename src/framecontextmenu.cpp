#include "framecontextmenu.h"
#include "textinputdialog.h"

#include <QGraphicsView>

FrameContextMenu::FrameContextMenu(Frame* const frame, QWidget *parent) :
    QMenu(parent), mFrame(frame)
{
    mRenameAction = addAction("Rename frame");
    setTitle(mFrame->getName());
}

void FrameContextMenu::execute() {
    QGraphicsView* const view = mFrame->getView();
    QPoint viewPoint = view->mapFromScene(mFrame->getPosition());
    viewPoint.setX(viewPoint.x() - mFrame->getDimensions().width());

    QAction* action = exec(view->viewport()->mapToGlobal(viewPoint));

    if(action == mRenameAction) {
        TextInputDialog d(this);
        d.setWindowTitle(QString("Rename frame"));
        d.setText(mFrame->getName());
        if(d.exec() == QDialog::Accepted) {
            //@TODO make sure not empty
            mFrame->setName(d.getText());
        }
    }
}

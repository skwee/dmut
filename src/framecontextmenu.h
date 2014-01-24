#ifndef FRAMECONTEXTMENU_H
#define FRAMECONTEXTMENU_H

#include <QMenu>

#include "frame.h"

class FrameContextMenu : public QMenu
{
    Q_OBJECT
public:
    explicit FrameContextMenu(Frame* const frame, QWidget* parent = 0);

    void execute();

signals:

public slots:

private:
    Frame* const mFrame;
    QAction* mRenameAction;
};

#endif // FRAMECONTEXTMENU_H

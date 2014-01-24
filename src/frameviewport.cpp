#include "frameviewport.h"

#include <QStyle>
#include <QMouseEvent>
#include <QMenu>

#include "framecontextmenu.h"

FrameViewport::FrameViewport(QWidget *parent) :
    QGraphicsView(parent), mFrameSet(nullptr), mSelectionRect(nullptr), mActiveFrame(nullptr)
{
    mScene = new QGraphicsScene();
    setScene(mScene);

    mSelectionRect = new QGraphicsRectItem();
    mSelectionRect->setBrush(QBrush(QColor(128, 128, 255, 128)));
    mSelectionRect->setPen(QPen());
}

FrameViewport::~FrameViewport() {
    if(mScene != nullptr) delete mScene;
}

void FrameViewport::startNewSession(const QString &spriteFileName, const Frame::Options &options) {
    if(mFrameSet != nullptr) {
        delete mFrameSet;
    }

    mFrameSet = new FrameSet(spriteFileName, options);

    mScene->clear();
    mFrameSet->addSetToScene(mScene);

    mSelectionRect->setRect(0, 0, options.width, options.height);
    mScene->addItem(mSelectionRect);

    show();

    yeildFrameSelectionChanged();
}

void FrameViewport::mousePressEvent(QMouseEvent *e) {
    if(mFrameSet == nullptr) return;

    QPointF pos = mapToScene(e->pos());
    const Frame::Options o = mFrameSet->getFrameOptions();
    QSize s = mFrameSet->getSpriteSize();

    if(pos.x() < 0) pos.setX(0);
    if(pos.x() > s.width() - o.width) pos.setX(s.width() - o.width);
    if(pos.y() < 0) pos.setY(0);
    if(pos.y() > s.height() - o.height) pos.setY(s.height() - o.height);

    mSelectionRect->setPos(
                (static_cast<unsigned int>(pos.x()) / o.width) * o.width,
                (static_cast<unsigned int>(pos.y()) / o.height) * o.height
                );

    yeildFrameSelectionChanged();

    if((e->button() == Qt::RightButton) && (mActiveFrame != nullptr)) {
        FrameContextMenu menu(mActiveFrame);
        menu.execute();
    }
}

void FrameViewport::keyPressEvent(QKeyEvent *e) {
    if(mFrameSet == nullptr) return;

    QPointF pos = mSelectionRect->pos();
    const Frame::Options o = mFrameSet->getFrameOptions();
    QSize s = mFrameSet->getSpriteSize();

    switch(e->key()) {
    case Qt::Key_Left:
        pos.setX(pos.x() - o.width);
        break;
    case Qt::Key_Right:
        pos.setX(pos.x() + o.width);
        break;
    case Qt::Key_Down:
        pos.setY(pos.y() + o.height);
        break;
    case Qt::Key_Up:
        pos.setY(pos.y() - o.height);
        break;
    }

    if(pos.x() < 0) pos.setX(0);
    if(pos.x() > s.width() - o.width) pos.setX(s.width() - o.width);
    if(pos.y() < 0) pos.setY(0);
    if(pos.y() > s.height() - o.height) pos.setY(s.height() - o.height);

    mSelectionRect->setPos(pos);

    yeildFrameSelectionChanged();
}

void FrameViewport::yeildFrameSelectionChanged() {
    Frame* previous = mActiveFrame;
    mActiveFrame = mFrameSet->getFrameAt(mSelectionRect->pos());
    emit selectedFrameChanged(previous, mActiveFrame);
}

#ifndef FRAMELISTFRAME_H
#define FRAMELISTFRAME_H

#include <QFrame>

#include "frame.h"
#include "spritefactory.h"
#include "framemodel.h"

namespace Ui {
class FrameListFrame;
}

class FrameListFrame : public QFrame
{
    Q_OBJECT
public:
    explicit FrameListFrame(QWidget *parent = 0);
    ~FrameListFrame();

    void createSpriteList(const QString &spriteFileName, const Frame::Options &options);

signals:
    void spriteToBeAddedToAnimation(Frame* sprite);

private slots:
    void on_changeLayoutButton_clicked();

    void onNameChangeAttemp(bool succeed, Frame::Namer::NameValidity reason);
    void onItemDoubleClicked(const QModelIndex& index);

private:
    void updateButtons();

    Ui::FrameListFrame *mUi;

    FrameModel* mFrameModel;
};

#endif // FRAMELISTFRAME_H

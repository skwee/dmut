#ifndef FRAMELISTFRAME_H
#define FRAMELISTFRAME_H

#include <QFrame>

#include "frame.h"

namespace Ui {
class FrameListFrame;
}

class FrameListFrame : public QFrame
{
    Q_OBJECT

public:
    explicit FrameListFrame(QWidget *parent = 0);
    ~FrameListFrame();

    void setDisabled(bool disabled);
    void createFrameList(const QString &spriteFileName, const Frame::Options &frameOptions);

private slots:
    void on_changeLayoutButton_clicked();

private:
    void updateButtons();

    Ui::FrameListFrame *mUi;
};

#endif // FRAMELISTFRAME_H

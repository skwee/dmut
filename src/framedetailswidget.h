#ifndef FRAMEDETAILSWIDGET_H
#define FRAMEDETAILSWIDGET_H

#include <QWidget>

namespace Ui {
class FrameDetailsWidget;
}

class FrameDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FrameDetailsWidget(QWidget *parent = 0);
    ~FrameDetailsWidget();

private:
    Ui::FrameDetailsWidget *ui;
};

#endif // FRAMEDETAILSWIDGET_H

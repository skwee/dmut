#include "framedetailswidget.h"
#include "ui_framedetailswidget.h"

FrameDetailsWidget::FrameDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrameDetailsWidget)
{
    ui->setupUi(this);
}

FrameDetailsWidget::~FrameDetailsWidget()
{
    delete ui;
}

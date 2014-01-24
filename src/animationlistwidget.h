#ifndef ANIMATIONLISTWIDGET_H
#define ANIMATIONLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class AnimationListWidget;
}

class AnimationListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationListWidget(QWidget *parent = 0);
    ~AnimationListWidget();

private slots:
    void on_addAnimationButton_clicked();

    void on_removeAnimationButton_clicked();

    void on_animationsList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::AnimationListWidget *mUi;
    QListWidgetItem* mCurrentSelectedItem;
};

#endif // ANIMATIONLISTWIDGET_H

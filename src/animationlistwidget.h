#ifndef ANIMATIONLISTWIDGET_H
#define ANIMATIONLISTWIDGET_H

#include <QTreeWidget>

#include "framelistwidget.h"

class AnimationListItem: public QTreeWidgetItem {
private:
    static unsigned int sIndex;

public:
    AnimationListItem();

    void resetName();
    void updatePreviousName();

private:
    QString mPreviousName;
};

class FrameAnimationListItem: public QTreeWidgetItem {
public:
    FrameAnimationListItem(Frame* frame);

    Frame* getFrame() const { return mFrame; }

private:
    Frame* mFrame;
};

class AnimationListWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit AnimationListWidget(QWidget *parent = 0);

    void addNewAnimation();
    void removeSelectedAnimations();

signals:

public slots:
    void onFrameAdd(QListWidgetItem* item);

private slots:
    void onItemChanged(QTreeWidgetItem* item, int column);
    bool isNameUnique(const QString& name, int column, QTreeWidgetItem* ignore = nullptr);
};

#endif // ANIMATIONLISTWIDGET_H

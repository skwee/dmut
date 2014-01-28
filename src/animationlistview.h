#ifndef ANIMATIONLISTVIEW_H
#define ANIMATIONLISTVIEW_H

#include <QListView>

#include "animationmodel.h"

class AnimationListView : public QListView
{
    Q_OBJECT
public:
    explicit AnimationListView(QWidget *parent = 0);
    ~AnimationListView();

private slots:
    void onInvalidName(AnimationModel::InvalidNameReason reason);

private:
    AnimationModel* mModel;
};

#endif // ANIMATIONLISTVIEW_H

#ifndef ANIMATION_H
#define ANIMATION_H

#include <QListWidgetItem>

class Animation: public QListWidgetItem
{
public:
    explicit Animation(const QString& name);

    QString getName() const { return mName; }
    void setName(const QString& name);

private:
    QString mName;
};

#endif // ANIMATION_H

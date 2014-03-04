#ifndef SPRITEATLASDIALOG_H
#define SPRITEATLASDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

#include "spriteatlasmodel.h"

namespace Ui {
class SpriteAtlasDialog;
}

class SpriteAtlasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpriteAtlasDialog(const QString &fileName, const Sprite::Size &size, QWidget *parent = 0);
    ~SpriteAtlasDialog();

private:
    Ui::SpriteAtlasDialog *mUi;
    QGraphicsScene* mScene;
};

#endif // SPRITEATLASDIALOG_H

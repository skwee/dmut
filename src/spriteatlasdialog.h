#ifndef SPRITEATLASDIALOG_H
#define SPRITEATLASDIALOG_H

#include <QDialog>
#include <QGraphicsScene>

#include "spriteatlasmodel.h"
#include "spriteatlasscene.h"

namespace Ui {
class SpriteAtlasDialog;
}

class SpriteAtlasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpriteAtlasDialog(const QString &fileName, const Sprite::Size &size, QWidget *parent = 0);
    ~SpriteAtlasDialog();

signals:
    void onSpriteSelected(Sprite* sprite);

private slots:
    void itemSelected();

private:
    Ui::SpriteAtlasDialog *mUi;
    SpriteAtlasScene* mScene;
};

#endif // SPRITEATLASDIALOG_H

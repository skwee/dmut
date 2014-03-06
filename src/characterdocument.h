#ifndef CHARACTERDOCUMENT_H
#define CHARACTERDOCUMENT_H

#include <QWidget>

#include "character.h"
#include "charactermodel.h"
#include "sprite.h"

class CharacterDocument: public QObject
{
    Q_OBJECT
public:
    static const char HEADER[];
    static const unsigned short VERSION;
    static const char TYPE_CHARACTER;
    static const char TYPE_ANIMATION;
    static const char TYPE_FRAME;

    static CharacterDocument* create(QWidget* parent = 0);
    ~CharacterDocument();

    inline CharacterModel* model() const { return mModel; }
    inline Sprite::Size frameSize() const { return mFrameSize; }

    inline bool isDirty() const { return mDirty; }

    void save(bool showSaveAs, QWidget* parent = 0);

signals:
    void onAddItemAction(const QModelIndex& index);
    void onRemoveItemAction(const QModelIndex& index);
    void onItemSelectionChanged(const QModelIndex& selected, const QModelIndex& deselected);
    void onModelChanged();

public slots:
    void spriteAtlasCreated(const QString& name);

private slots:
    void modelChanged();
    void stateChanged();

private:
    CharacterDocument(const QString& name, const Sprite::Size& frameSize);

    Sprite::Size mFrameSize;
    Character* mCharacter;
    CharacterModel* mModel;
    bool mDirty;
    QString mFilePath;
    QString mSpriteAtlas;
};

#endif // CHARACTERDOCUMENT_H

#include "characterdocument.h"
#include "newcharacterdialog.h"
#include "namer.h"
#include "animation.h"
#include "frame.h"

#include <QFileDialog>

const char CharacterDocument::HEADER[] = {'D', 'M', 'U', 'T'};
const unsigned short CharacterDocument::VERSION = 1;
const char CharacterDocument::TYPE_CHARACTER = 'C';
const char CharacterDocument::TYPE_ANIMATION = 'A';
const char CharacterDocument::TYPE_FRAME = 'F';

CharacterDocument* CharacterDocument::create(QWidget* parent) {
    Namer::reset();

    NewCharacterDialog nc(Namer::generateCharacterName(), parent);
    if(nc.exec() == QDialog::Accepted) {
        return new CharacterDocument(nc.getCharacterName(), nc.getFrameSize());
    }
    return nullptr;
}

CharacterDocument::CharacterDocument(const QString &name, const Sprite::Size& frameSize) :
    mCharacter(nullptr), mModel(nullptr), mDirty(true), mFilePath("")
{
    mCharacter = new Character(name);
    mFrameSize = frameSize;
    mModel = new CharacterModel(mCharacter);

    QObject::connect(
                this, SIGNAL(onAddItemAction(QModelIndex)),
                mModel, SLOT(addItemTo(QModelIndex))
                );

    QObject::connect(
                this, SIGNAL(onRemoveItemAction(QModelIndex)),
                mModel, SLOT(removeItem(QModelIndex))
                );


    QObject::connect(
                mModel, SIGNAL(changed()),
                this, SLOT(modelChanged())
                );

    QObject::connect(
                this, SIGNAL(onAddItemAction(QModelIndex)),
                this, SLOT(stateChanged())
                );

    QObject::connect(
                this, SIGNAL(onRemoveItemAction(QModelIndex)),
                this, SLOT(stateChanged())
                );

    QObject::connect(
                mModel, SIGNAL(changed()),
                this, SLOT(stateChanged())
                );
}

CharacterDocument::~CharacterDocument() {
    if(mModel) delete mModel;
}

void CharacterDocument::spriteAtlasCreated(const QString &name) {
    mSpriteAtlas = name;
}

void CharacterDocument::modelChanged() {
    emit onModelChanged();
}

void CharacterDocument::save(bool showSaveAs, QWidget* parent) {
    if(mFilePath.isEmpty() || showSaveAs) {
        mFilePath = QFileDialog::getSaveFileName(parent, QObject::tr("Save As"), QDir::homePath(), "dmut File (*.dmut)");
    }

    if(mFilePath.isEmpty()) {
        //@TODO
        return;
    }

    if(mFilePath.indexOf(".dmut") == -1) {
        mFilePath += ".dmut";
    }

    QFile file(mFilePath);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out.writeRawData(HEADER, sizeof(HEADER));
    out << static_cast<unsigned short>(VERSION);

    out << mSpriteAtlas.length();
    out.writeRawData(mSpriteAtlas.toStdString().c_str(), mSpriteAtlas.length());

    if(mModel->root()->children().length() > 0) {
        Character* c = static_cast<Character*>(mModel->root()->children().at(0));
        out.writeRawData(&TYPE_CHARACTER, sizeof(char));
        out << c->name().length();
        out.writeRawData(c->name().toStdString().c_str(), c->name().length());

        for(Item* i : c->children()) {
            Animation* a = static_cast<Animation*>(i);
            out.writeRawData(&TYPE_ANIMATION, sizeof(char));
            out << a->name().length();
            out.writeRawData(a->name().toStdString().c_str(), a->name().length());
            char wm = a->getWrapMode();
            out.writeRawData(&wm, sizeof(char));
            unsigned short len = a->getLength() * 1000;
            out << static_cast<unsigned short>(len);
        }

        for(Item* ia: c->children()) {
            unsigned int connection = 0;
            for(Item* i: ia->children()) {
                Frame* f = static_cast<Frame*>(i);
                out.writeRawData(&TYPE_FRAME, sizeof(char));
                out << f->name().length();
                out.writeRawData(f->name().toStdString().c_str(), f->name().length());
                char hold = f->getHold();
                out.writeRawData(hold, sizeof(char));
                Sprite* s = f->getSprite();
                if(s) {
                    out << s->offset().x;
                    out << s->offset().y;
                } else {
                    out << static_cast<unsigned int>(-1);
                    out << static_cast<unsigned int>(-1);
                }
                out << connection;
            }
            connection ++;
        }
    }

    file.flush();
    file.close();

    mDirty = false;
}

void CharacterDocument::stateChanged() {
    mDirty = true;
}

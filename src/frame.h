#ifndef FRAME_H
#define FRAME_H

#include <QPixmap>

#include "item.h"

class Frame: public Item {
public:
    class Namer {
    private:
        static unsigned int sFrameIndex;
        static unsigned int sTotalFrames;
        static unsigned int getNumberOfFrames();

    public:
        static void initialize(unsigned int total);
        static QString generate();
    };

    typedef struct {
        unsigned int width;
        unsigned int height;
    }Options;

    Frame(QPixmap pixmap, Item* parent = nullptr);

    virtual QVariant decoration() const override;

private:
    QPixmap mPixmap;
};

#endif // FRAME_H

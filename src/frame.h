#ifndef FRAME_H
#define FRAME_H

#include <QPixmap>

class Frame {
public:
    class Namer {
    private:
        static unsigned int sFrameIndex;
        static unsigned int sTotalFrames;
        static unsigned int getNumberOfFrames();

    public:
        static const int MAX_LENGTH = 32;

        enum class NameValidity {
            Valid,
            Empty,
            TooLong,
            Duplicate
        };

        static void initialize(unsigned int total);
        static QString generate();
        static NameValidity validate(const QString& name);

    };

    typedef struct {
        unsigned int width;
        unsigned int height;
    }Options;

    Frame(QPixmap pixmap);

    void setName(const QString& name) { mName = name; }
    QString getName() const { return mName; }

    const QPixmap& getPixmap() const { return mPixmap; }

private:
    QString mName;
    QPixmap mPixmap;
};

#endif // FRAME_H

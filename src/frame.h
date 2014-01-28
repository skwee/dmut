#ifndef FRAME_H
#define FRAME_H

#include <QAbstractItemModel>
#include <QPixmap>
#include <memory>

class Frame {
private:
    static unsigned int sFrameIndex;
    static unsigned int sTotalFrames;

    static unsigned int getNumberOfFrames() {
        return sTotalFrames > 0 ? (int) log10 ((double) sTotalFrames) + 1 : 1;
    }

public:
    typedef std::shared_ptr<Frame> Ptr;

    static void setTotalFrames(unsigned int total) { sTotalFrames = total; }

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

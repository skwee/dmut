#ifndef FRAME_H
#define FRAME_H

#include <QPixmap>

class Frame: public QObject {
    Q_OBJECT
private:
    static unsigned int sFrameIndex;
    static unsigned int sTotalFrames;

    static unsigned int getNumberOfFrames() {
        return sTotalFrames > 0 ? (int) log10 ((double) sTotalFrames) + 1 : 1;
    }

public:
    static void setTotalFrames(unsigned int total) { sTotalFrames = total; }

    typedef struct {
        unsigned int width;
        unsigned int height;
    }Options;

    Frame(QPixmap pixmap);

    const QString& getName() const { return mName; }
    void setName(const QString& name);

    const QPixmap& getPixmap() const { return mPixmap; }

signals:
    void nameChanged(const QString& name);

private:
    QString mName;
    QPixmap mPixmap;
};

#endif // FRAME_H

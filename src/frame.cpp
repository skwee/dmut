#include "frame.h"

unsigned int Frame::sFrameIndex = 0;
unsigned int Frame::sTotalFrames = 1;

Frame::Frame(QPixmap pixmap)
    :mPixmap(pixmap)
{
    setName(QString("Frame %1").arg(++sFrameIndex, getNumberOfFrames(), 10, QChar('0')));
}

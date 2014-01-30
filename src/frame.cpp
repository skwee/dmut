#include "frame.h"

unsigned int Frame::Namer::sFrameIndex = 0;
unsigned int Frame::Namer::sTotalFrames = 1;

unsigned int Frame::Namer::getNumberOfFrames() {
    return sTotalFrames > 0 ? (int) log10 ((double) sTotalFrames) + 1 : 1;
}

void Frame::Namer::initialize(unsigned int total) {
    sTotalFrames = total;
    sFrameIndex = 0;
}

QString Frame::Namer::generate() {
    return QString("Sprite %1").arg(++sFrameIndex, getNumberOfFrames(), 10, QChar('0'));
}

Frame::Namer::NameValidity Frame::Namer::validate(const QString &name) {
    int l = name.length();
    if(l == 0) return NameValidity::Empty;
    if(l > MAX_LENGTH) return NameValidity::TooLong;
    return NameValidity::Valid;
}


Frame::Frame(QPixmap pixmap)
    :mPixmap(pixmap)
{
    setName(Namer::generate());
}

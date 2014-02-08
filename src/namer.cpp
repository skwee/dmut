#include "namer.h"

unsigned int Namer::sCharacterIndex = 0;
unsigned int Namer::sAnimationIndex = 1;
unsigned int Namer::sFrameIndex = 1;

void Namer::reset() {
    sCharacterIndex = 0;
    sAnimationIndex = 1;
    sFrameIndex = 1;
}

QString Namer::generateCharacterName() {
    return QString("character_%1").arg(sCharacterIndex++);
}

QString Namer::generateAnimationName() {
    return QString("animation_%1").arg(sAnimationIndex++);
}

QString Namer::generateFrameName() {
    return QString("frame_%1").arg(sFrameIndex++);
}

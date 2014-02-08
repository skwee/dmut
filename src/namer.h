#ifndef NAMER_H
#define NAMER_H

#include <QString>

class Namer
{
private:
    static unsigned int sCharacterIndex;
    static unsigned int sAnimationIndex;
    static unsigned int sFrameIndex;

public:
    static void reset();

    static QString generateCharacterName();
    static QString generateAnimationName();
    static QString generateFrameName();
};

#endif // NAMER_H

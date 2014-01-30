#include "animation.h"

unsigned int Animation::Namer::sIndex = 0;

QString Animation::Namer::generate() {
    return QString("Animation %1").arg(sIndex++);
}

Animation::Namer::NameValidity Animation::Namer::validate(const QString &name) {
    int l = name.length();
    if(l == 0) return NameValidity::Empty;
    if(l > MAX_LENGTH) return NameValidity::TooLong;
    return NameValidity::Valid;
}

Animation::Animation() :
    mFramesPerSecond(DEFAULT_FPS)
{
    setName(Namer::generate());
}

Animation::~Animation() {
    qDeleteAll(mFrames);
}

void Animation::addFrame(Frame* frame) {
    AnimationFrame* af = new AnimationFrame(frame);
    mFrames.push_back(af);
}

AnimationFrame* Animation::frameAt(int index) const {
    if(index < mFrames.size()) return mFrames.at(index);
    return nullptr;
}

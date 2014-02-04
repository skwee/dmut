#ifndef SK_DMUT_ANIMATION_H
#define SK_DMUT_ANIMATION_H

#include <string>
#include <memory>

namespace sk {
namespace dmut {

class Animation {
public:
    typedef std::shared_ptr<Animation*> ptr;
    typedef unsigned char FramesPerSecond;

    const FramesPerSecond MAX_FPS = 255;

    Animation();

    inline std::string name() const { return mName; }
    inline void setName(const std::string& name) { mName = name; }

    inline FramesPerSecond fps() const { return mFps; }
    inline void setFps(FramesPerSecond fps) { mFps = fps; }

    inline bool loop() const { return mLoop; }
    inline void setLoop(bool loop) { mLoop = loop; }

private:
    std::string mName;
    FramesPerSecond mFps;
    bool mLoop;
};

}
}

#endif // SK_DMUT_ANIMATION_H

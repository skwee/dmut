#ifndef SK_DMUT_FRAME_H
#define SK_DMUT_FRAME_H

#include <string>
#include <memory>

namespace sk {
namespace dmut {

class Frame {
public:
    typedef std::shared_ptr<Frame*> ptr;

    typedef unsigned char Hold;
    typedef struct{
        unsigned int x, y;
    }Offset;

    const Hold MAX_HOLD = 255;

    Frame();

    inline std::string name() const { return mName; }
    inline void setName(const std::string& name) { mName = name; }

    inline Hold hold() const { return mHold; }
    inline void setHold(Hold hold) { mHold = hold; }

    inline Offset offset() const { return mOffset; }
    inline void setOffest(const Offset& offset) { mOffset = offset; }

private:
    std::string mName;
    Hold mHold;
    Offset mOffset;
};

}
}

#endif // SK_DMUT_FRAME_H

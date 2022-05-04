#ifndef DENGINE_FRAMEBUFFER_H
#define DENGINE_FRAMEBUFFER_H
#include "core/Types.h"
namespace  DEngine {

    class FrameBuffer {

    public:
        FrameBuffer();
        ~FrameBuffer();
    private:
        uint frameBufferID;
    };
}
#endif

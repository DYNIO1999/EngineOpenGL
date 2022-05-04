#ifndef DENGINE_FRAMEBUFFER_H
#define DENGINE_FRAMEBUFFER_H
#include "core/Types.h"
#include "Renderer.h"

namespace  DEngine {

    class FrameBuffer {

    public:
        FrameBuffer();
        ~FrameBuffer();


        void bind();
        void unBind();
        void createColorAttachmentTexture(uint slot =0);
        uint getColorAttachmentTexture() const { return  frameColorAttachmentTextureID;}

    private:
        uint frameColorAttachmentTextureID;
        uint frameBufferID;
    };
}
#endif

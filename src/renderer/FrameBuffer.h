#ifndef DENGINE_FRAMEBUFFER_H
#define DENGINE_FRAMEBUFFER_H
#include <assert.h>
#include "core/Types.h"
#include "Renderer.h"
#include "core/LogManager.h"


namespace  DEngine {


    struct FramebufferSpecification
    {
        uint width = 0;
        uint height = 0;
        uint samples = 1;
    };

    class FrameBuffer {

    public:
        FrameBuffer(const FramebufferSpecification& specs);
        ~FrameBuffer();

        void bind();
        void unBind();
        void bindTexture(uint slot =0);
        //uint get() const { return  frameColorAttachmentTextureID;}

    private:
        uint frameBufferTextureID;
        uint frameBufferID;
        FramebufferSpecification framebufferSpecification;
    };
}
#endif

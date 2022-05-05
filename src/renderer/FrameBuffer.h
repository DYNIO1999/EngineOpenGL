#ifndef DENGINE_FRAMEBUFFER_H
#define DENGINE_FRAMEBUFFER_H
#include <assert.h>
#include "core/Types.h"
#include "Renderer.h"
#include "core/LogManager.h"


namespace  DEngine {


    struct FramebufferSpecification
    {
        int width = 0;
        int height = 0;
        int samples = 1;
    };

    class FrameBuffer {

    public:
        FrameBuffer(const FramebufferSpecification& _specs);
        ~FrameBuffer();

        void bind();
        void unBind();
        void bindTexture(uint _slot =0);
        uint getTexture()const{return frameBufferTextureID;};
        uint getRenderBufferObject()const{return renderBufferObject;};


    private:
        uint renderBufferObject;
        uint frameBufferTextureID;
        uint frameBufferID;
        FramebufferSpecification framebufferSpecification;
    };
}
#endif

#include "FrameBuffer.h"
#include "core/Engine.h"
namespace DEngine{

    FrameBuffer::FrameBuffer(const FramebufferSpecification& _specs):
            framebufferSpecification(_specs)
    {
        glGenFramebuffers(1, &frameBufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
        bool multisample = framebufferSpecification.samples > 1;

        glGenTextures(1, &frameBufferTextureID);
        glBindTexture(GL_TEXTURE_2D, frameBufferID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, framebufferSpecification.width, framebufferSpecification.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTextureID, 0);


        glGenRenderbuffers(1, &renderBufferObject);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObject);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebufferSpecification.width,framebufferSpecification.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObject);

        DENGINE_ERROR("Framebuffer is incomplete!");
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1,&frameBufferID);
        glDeleteTextures(1,&frameBufferTextureID);
    }
    void FrameBuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
    }
    void FrameBuffer::unBind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void FrameBuffer::bindTexture(uint _slot) {
        glActiveTexture(GL_TEXTURE0+_slot);
        glBindTexture(GL_TEXTURE_2D,frameBufferTextureID);
    }
}

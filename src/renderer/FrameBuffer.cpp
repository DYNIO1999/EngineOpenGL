#include "FrameBuffer.h"

namespace DEngine{

    FrameBuffer::FrameBuffer(const FramebufferSpecification& specs) {
        glGenFramebuffers(1, &frameBufferID);


        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
    }
    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1,&frameBufferID);
        glDeleteTextures(1,&frameColorAttachmentTextureID);
    }
    void FrameBuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

        //glGenTextures(1, &textureColorbuffer);
        //glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    }
    void FrameBuffer::unBind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    void FrameBuffer::bindTexture(uint slot) {

    }
}

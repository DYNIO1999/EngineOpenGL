#include "Texture.h"
#include <cassert>
#include "core/LogManager.h"
#include "Renderer.h"
namespace DEngine{
    Texture::Texture(const std::string &path):
    textureID(0),
    localTextureBuffer(nullptr),
    width(0),
    height(0),
    bitPerPixel(0)
    {
        stbi_set_flip_vertically_on_load(1);
        localTextureBuffer = stbi_load(path.c_str(),&width, &height, &bitPerPixel,4);
        if(!localTextureBuffer) {
            DENGINE_ERROR("Cant read data from given texture!\n");
            assert(localTextureBuffer != nullptr);
        }
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D,textureID);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,height,0,GL_RGBA, GL_UNSIGNED_BYTE, localTextureBuffer);
        glBindTexture(GL_TEXTURE_2D,0);
        if(localTextureBuffer){
            stbi_image_free(localTextureBuffer);
        }
    }
    Texture::~Texture() {
        glDeleteTextures(1,&textureID);
    }
    void Texture::bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0+slot);
        glBindTexture(GL_TEXTURE_2D,textureID);
    }
    void Texture::unbind() {
        glBindTexture(GL_TEXTURE_2D,0);
    }
}

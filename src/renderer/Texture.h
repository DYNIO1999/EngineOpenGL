#ifndef DENGINE_TEXTURE_H
#define DENGINE_TEXTURE_H
#include <string>
#include "stb_image.h"

namespace DEngine {
    class Texture {
    public:
        Texture() = default;
        Texture(const Texture&) = default;
        Texture(const std::string& path, bool _filp = false);
        ~Texture();

        void bind(unsigned int slot =0);
        void unbind();
    private:
        unsigned int textureID;
        unsigned char* localTextureBuffer;
        int width, height, bitPerPixel;
    };
}
#endif
#include "CubeMap.h"


namespace DEngine{
    void CubeMap::loadCubeMap() {
        glGenTextures(1, &cubeMapID);
        glBindTexture(GL_TEXTURE_CUBE_MAP,cubeMapID);
        int width, height, nrChannels;
        for (unsigned int i = 0; i < cubeFaces.size(); i++)
        {
            unsigned char *data = stbi_load(cubeFaces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                DENGINE_ERROR("Cubemap texture failed to load at path: {}",cubeFaces[i]);
                stbi_image_free(data);
            }
        }
    }
    void CubeMap::bind(unsigned int slot) {
        glActiveTexture(GL_TEXTURE0+slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
    }
    void CubeMap::unbind() {

        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
    }



}
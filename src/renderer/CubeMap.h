#ifndef DENGINE_CUBEMAPS_H
#define DENGINE_CUBEMAPS_H
#include "core/Engine.h"
#include "Renderer.h"
namespace  DEngine {
    class CubeMap {
    public:
        CubeMap(const std::vector<std::string>& _cubeFaces)
        :cubeFaces(_cubeFaces)
        {
            loadCubeMap();
        }
        ~CubeMap(){

        }
        void bind(unsigned int slot =0);
        void unbind();

    private:
        void loadCubeMap();
        unsigned int cubeMapID;
        unsigned char* cubeMapBuffer;

        std::vector<std::string> cubeFaces;
    };
}
#endif

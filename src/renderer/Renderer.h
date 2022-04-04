#ifndef DENGINE_RENDERER_H
#define DENGINE_RENDERER_H
#include <glm/glm.hpp>
#include "../core/LogManager.h"

namespace  DEngine {


    //struct RenderData{
    //    virtual ~RenderData();
    //    //{VertexAObject
    //    //{VertexBufferObject
    //    //{VertexLayout
    //    //{VertexIndex
    //    //Mesh
    //    //Texture
    //};

    class Renderer {
    public:
        //Renderer(Renderer &other) = delete;
        //void operator=(const Renderer &) = delete;

        static void init();
        //static void submit(); MeshPass
        static void begineDraw(glm::mat4 projection);

        //static void submit(); TexturesPass

        static void submit(); //rawData
        //static void submit(); //Primitive
        static void endDraw();

        static void shutdown();

        static Renderer* getInstance();

    private:
        Renderer(){

        }
        static Renderer* renderer;
    };
    //std::vector<RemderData> renderDataList;
}
#endif

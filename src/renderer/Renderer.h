#ifndef DENGINE_RENDERER_H
#define DENGINE_RENDERER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/ext.hpp>

#include <cassert>
#include <vector>

#include "../core/LogManager.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include "components/Components.h"

namespace  DEngine {
    static const std::string PATH_TEXTURES = "../../resources/textures/";
    static const std::string PATH_SHADERS = "../../resources/shaders/";
    static const std::string PATH_MODELS = "../../resources/models/";

    static const std::string PATH_MODELS_GAME = "../../resources/models/bombingSimulator/";
    static const std::string PATH_TEXTURES_GAME = "../../resources/textures/bombingSimulator/";
    static const std::string PATH_SHADERS_GAME = "../../resources/shaders/bombingSimulator/";


    struct DrawCallSettings{
        DrawCallSettings():
        enableBlendingFlag(false),
        enableDepthTestFlag(false),
        enableStencilBufferFlag(false),
        clearColorBufferFlag(true){
        }
        
        bool enableBlendingFlag;
        bool enableDepthTestFlag;
        bool enableStencilBufferFlag;
        bool clearColorBufferFlag;
    };

    struct DrawCallData{

    };


    class Renderer {
    public:
        Renderer(Renderer &other) = delete;
        void operator=(const Renderer &) = delete;

        void init();
        void beginDraw(glm::mat4 _projection);
        void beginDraw(glm::mat4 _projection, const DrawCallSettings& settings);
        void draw(VertexArray &va, IndexBuffer &ib, Shader &shader, unsigned int type = GL_TRIANGLES);
        void draw(VertexArray &va, Shader &shader, unsigned int type=  GL_TRIANGLES);

        void draw(Mesh &mesh, Shader &shader);
        void drawDebug(Mesh &mesh, Shader &shader);
        void draw(MeshComponent& _meshComponent, Shader& _shader);
        void endDraw();
        void shutdown();
        void clear() const;
        void clear(glm::vec4 _givenColor) const;
        static Renderer* getInstance();



        void setDepthMask(bool _set);

    private:
        glm::mat4  currentProjection;
        Renderer(){
        }
        static Renderer* renderer;
        DrawCallSettings currentDrawCallSettings;


    };
}
#endif

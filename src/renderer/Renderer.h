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
namespace  DEngine {

    static const std::string PATH_TEXTURES = "../../resources/textures/";
    static const std::string PATH_SHADERS = "../../resources/shaders/";




    typedef enum {
        CHAR,
        INT,
        FLOAT,
        DOUBLE
    } TYPES;


    struct VertexData{
        glm::vec3 position;
        glm::vec2 texturePosition;
    };

    struct DrawCallSettings{
        DrawCallSettings():
        enableBlendingFlag(false),
        enableDepthFlag(false),
        enableStencilFlag(false),
        clearColorBufferFlag(true){
        }
        
        bool enableBlendingFlag;
        bool enableDepthFlag;
        bool enableStencilFlag;
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
        void endDraw();
        void shutdown();
        void clear() const;
        void clear(glm::vec4 _givenColor) const;
        static Renderer* getInstance();

    private:
        glm::mat4  currentProjection;
        Renderer(){
        }
        static Renderer* renderer;
        DrawCallSettings currentDrawCallSettings;


    };
}
#endif

#include "Renderer.h"
#include <glad/glad.h>

namespace DEngine{
    Renderer* Renderer::renderer= nullptr;

    void OpenGLMessageCallback(
            unsigned source,
            unsigned type,
            unsigned id,
            unsigned severity,
            int length,
            const char* message,
            const void* userParam)
    {
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         DENGINE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM:       DENGINE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_LOW:          DENGINE_WARN(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: DENGINE_TRACE(message); return;
        }
    }
    Renderer* Renderer::getInstance() {
        if(renderer==nullptr){
            renderer = new Renderer();
        }
        return renderer;
    }

    void Renderer::init() {

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
    }
    void Renderer::begineDraw(glm::mat4 projection) {
        //start initializing OpenGL to render
    }

    void Renderer::endDraw() {
        //clear Draw Data

    }

    void Renderer::submit() {

    }



    void Renderer::shutdown() {

    }



}
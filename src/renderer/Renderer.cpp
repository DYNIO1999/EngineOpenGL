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
    void Renderer::beginDraw(glm::mat4 _projection) {
        currentProjection = _projection;
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH);

    }
    void Renderer::beginDraw(glm::mat4 _projection, const DrawCallSettings& settings){
        currentProjection = _projection;
        currentDrawCallSettings = settings;
        currentDrawCallSettings.enableBlendingFlag ? glEnable(GL_BLEND) : (void)0;
        currentDrawCallSettings.enableDepthFlag ?  glEnable(GL_DEPTH): (void)0;
        currentDrawCallSettings.enableStencilFlag ? glEnable(GL_STENCIL) : (void)0;
    }
    void Renderer::draw(VertexArray &va, Shader &shader, unsigned int type) {
        shader.bind();
        va.bind();
        if (type == GL_POINTS){
            glDrawArrays(GL_POINTS, 0, va.getVertexCount());
        }
        else if (type == GL_LINES)
        {
            glDrawArrays(GL_LINES, 0, va.getVertexCount());
        }else{
            glDrawArrays(GL_TRIANGLES,0 ,va.getVertexCount());
        }
    }
    void Renderer::draw(VertexArray &va, IndexBuffer &ib, Shader &shader, unsigned int type) {
        shader.bind();
        va.bind();
        ib.bind();
        if (type == GL_POINTS){
            glDrawElements(GL_POINTS, ib.getCount(), GL_UNSIGNED_INT, nullptr);
        }
        else if (type == GL_LINES)
        {
            glDrawElements(GL_LINES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
        }else{
            glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
        }
    }


    void Renderer::clear() const {
        glClear
                (
                        (currentDrawCallSettings.clearColorBufferFlag ? GL_COLOR_BUFFER_BIT : 0) |
                        (currentDrawCallSettings.enableDepthFlag ? GL_DEPTH_BUFFER_BIT : 0) |
                        (currentDrawCallSettings.enableStencilFlag ? GL_STENCIL_BUFFER_BIT : 0)
                );
    }

    void Renderer::clear(glm::vec4 _givenColor) const {
        glClearColor(_givenColor.x, _givenColor.y, _givenColor.z, _givenColor.w);
        glClear

                (

                        (currentDrawCallSettings.clearColorBufferFlag ? GL_COLOR_BUFFER_BIT : 0) |

                        (currentDrawCallSettings.enableDepthFlag ? GL_DEPTH_BUFFER_BIT : 0) |

                        (currentDrawCallSettings.enableStencilFlag ? GL_STENCIL_BUFFER_BIT : 0)

                );
    }
    void Renderer::endDraw(){
        currentDrawCallSettings.enableBlendingFlag ? glDisable(GL_BLEND) : (void)0;
        currentDrawCallSettings.enableDepthFlag ? glDisable(GL_DEPTH) : (void)0;
        currentDrawCallSettings.enableStencilFlag ? glDisable(GL_STENCIL) : (void)0;
    }
    void Renderer::shutdown() {

    }
}
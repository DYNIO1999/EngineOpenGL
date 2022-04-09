#ifndef DENGINE_WAVESURFACESCENE_H
#define DENGINE_WAVESURFACESCENE_H
#include "core/SceneManager.h"
#include "core/Camera.h"

#include "renderer/Renderer.h"

#include "core/Window.h"

namespace  DEngine {

    class WaveSurfaceScene : public Scene {
    public:
        WaveSurfaceScene(std::string name, std::shared_ptr<Window> _windowPtr): Scene(name),
        testShader(PATH_SHADERS+ "wavesShaders/VertexShader.glsl",
                   PATH_SHADERS+ "wavesShaders/FragmentShader.glsl",
                   PATH_SHADERS+ "wavesShaders/TessellationControlShader.glsl",
                   PATH_SHADERS+ "wavesShaders/TessellationEvaluationShader.glsl"
                   ),
            windowPtr(_windowPtr)
        {
            initScene();
        };
        void initScene() override;
        void input(Event& e) override;
        void update() override;

        bool onKeyPressedInput(KeyPressedEvent& e);
        bool windowClose(WindowCloseEvent& e);
    private:

        bool onMouseMovedEvent(MouseMovedEvent& e);
        Shader testShader;
        Camera camera{glm::vec3(0.0f, 0.0f, 0.3f)};
        std::vector<glm::mat4> hair;
        glm::mat4 model, view, projection;
        std::shared_ptr<Window> windowPtr;
    };
}
#endif
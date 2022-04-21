#ifndef DENGINE_GPUPARTICLESSCENE_H
#define DENGINE_GPUPARTICLESSCENE_H
#include "core/Engine.h"
#include "core/Camera.h"

namespace  DEngine {
    class GPUParticlesScene :public Scene{
    public:

        GPUParticlesScene(std::string name, std::shared_ptr<Window> _windowPtr):
        Scene(name),
        computeShader(PATH_SHADERS+"particles/rain/RainComputeShader.glsl"),
        rainParticleShader(PATH_SHADERS+"particles/rain/RainVertexShader.glsl",
                           PATH_SHADERS+"particles/rain/RainGeometryShader.glsl",
                           PATH_SHADERS+"particles/rain/RainFragmentShader.glsl"),
        windowPtr(_windowPtr)
        {
            initScene();
        };
        void initScene() override;
        void input(Event& e) override;
        void update(float dt) override;

    private:
        bool onKeyPressedInput(KeyPressedEvent& e);
        bool windowClose(WindowCloseEvent& e);

        bool isButtonPressed;
        bool onMousePressed(MouseButtonPressed& e);
        bool onMouseReleased(MouseButtonReleased& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);
        void initSystems();
        std::shared_ptr<Window> windowPtr;
        Shader computeShader;
        Shader rainParticleShader;


        glm::mat4 model, view, projection;
        Camera camera{glm::vec3(0.0f, 0.0f, 0.3f)};
        std::shared_ptr<Mesh> testMesh;
        std::vector<Entity> entities;
    };
}
#endif
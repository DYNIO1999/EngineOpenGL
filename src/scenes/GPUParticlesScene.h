#ifndef DENGINE_GPUPARTICLESSCENE_H
#define DENGINE_GPUPARTICLESSCENE_H
#include "core/Engine.h"
#include "core/Camera.h"
#include "renderer/CubeMap.h"
namespace  DEngine {
    class GPUParticlesScene :public Scene{
    public:

        GPUParticlesScene(std::string name, std::shared_ptr<Window> _windowPtr):
        cubeMap({{PATH_TEXTURES+"skybox/right.jpg"},
                 {PATH_TEXTURES+"skybox/left.jpg"},
                 {PATH_TEXTURES+"skybox/top.jpg"},
                 {PATH_TEXTURES+"skybox/bottom.jpg"},
                 {PATH_TEXTURES+"skybox/front.jpg"},
                 {PATH_TEXTURES+"skybox/back.jpg"},}
                 ),
        Scene(name),
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


        glm::mat4 model, view, projection;
        Camera camera{glm::vec3(0.0f, 0.0f, 0.3f)};
        std::shared_ptr<Mesh> testMesh;
        std::vector<Entity> entities;

        std::shared_ptr<VertexArray> vertexArrayCube;
        std::shared_ptr<VertexBuffer> vertexBufferCube;
        std::shared_ptr<VertexBufferLayout> vertexBufferLayoutCube;

        std::shared_ptr<VertexArray> vertexArraySkybox;
        std::shared_ptr<VertexBuffer> vertexBufferSkybox;
        std::shared_ptr<VertexBufferLayout> vertexBufferLayoutSkybox;
        CubeMap cubeMap;
    };
}
#endif
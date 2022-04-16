#ifndef DENGINE_TESTSCENE_H
#define DENGINE_TESTSCENE_H

#include <unordered_set>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"


#include "core/Scene.h"
#include "renderer/Renderer.h"
#include "ecs/EntitySystemManager.h"

#include "core/Window.h"
#include "renderer/Model.h"
#include "core/Camera.h"

namespace DEngine {
    struct Position {
        float x;
        float y;
        float w;
        float h;
    };
    struct Color {
        float r;
        float g;
        float b;
    };

    class TestScene : public Scene {
    public:
        TestScene(std::string name, std::shared_ptr<Window> _windowPtr): Scene(name),
                                     testShader(PATH_SHADERS+ "TestVertexShader.glsl",PATH_SHADERS+ "TestFragmentShader.glsl" )
                                     ,textureTest(PATH_TEXTURES + "test.png")
                                     ,windowPtr(_windowPtr)
        {
            initData();
        };
        ~TestScene();
        void initScene() override{

        }
        void input(Event& e) override;

        void update(float dt) override;
        void detach() override;

        int counter = 0;



        int item_current_idx = 0;
        bool is_selected = false;
        float timeCounter;
        Shader testShader;

        Texture textureTest;
    private:
        void ImGUITest();
        void initData();

        bool onKeyPressedInput(KeyPressedEvent& e);
        bool windowClose(WindowCloseEvent& e);
        bool isButtonPressed;
        bool onMousePressed(MouseButtonPressed& e);
        bool onMouseReleased(MouseButtonReleased& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);

        Model testModel{PATH_MODELS+"hey/hey.gltf"};
        float currentDeltaTime;
        Camera camera{glm::vec3(0.0f, 0.0f, 0.3f)};

        std::shared_ptr<Mesh> testMesh;
        std::vector<Entity> entities;
        glm::mat4 model, view, projection;
        //std::shared_ptr<PhysicsSystem> physicsSystem
        std::shared_ptr<Window> windowPtr;

    };
}
#endif

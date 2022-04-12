#ifndef DENGINE_TESTSCENE_H
#define DENGINE_TESTSCENE_H

#include "core/Scene.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"
#include "renderer/Renderer.h"
#include "ecs/EntitySystemManager.h"
#include "core/Window.h"

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
        bool windowClose(WindowCloseEvent& e);

    private:
        void ImGUITest();
        void initData();


        std::vector<Entity> entities;
        glm::mat4 model, view, projection;
        //std::shared_ptr<PhysicsSystem> physicsSystem
        std::shared_ptr<Window> windowPtr;

    };
}
#endif

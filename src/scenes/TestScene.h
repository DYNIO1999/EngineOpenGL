#ifndef DENGINE_TESTSCENE_H
#define DENGINE_TESTSCENE_H

#include "core/Scene.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"
#include "renderer/Renderer.h"

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
        TestScene(std::string name): Scene(name),
                                     testShader(PATH_SHADERS+ "TestVertexShader.glsl",PATH_SHADERS+ "TestFragmentShader.glsl" )
        {

        };
        void initScene() override{

        }
        void input(Event& e) override;
        void update() override;
        int counter = 0;
        int item_current_idx = 0;
        bool is_selected = false;

        Shader testShader;
    };
}
#endif
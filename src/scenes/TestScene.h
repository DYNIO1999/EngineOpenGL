#ifndef DENGINE_TESTSCENE_H
#define DENGINE_TESTSCENE_H

#include "core/Scene.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"

namespace DEngine {
    class TestScene : public Scene {
    public:
        TestScene(std::string name): Scene(name){

        };

        void input(Event& e) override;
        void update() override;
        int counter = 0;
    };
}
#endif
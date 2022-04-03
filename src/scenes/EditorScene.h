#ifndef DENGINE_EDITOR_SCENE_H
#define DENGINE_EDITOR_SCENE_H

#include <memory>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"
#include "core/Scene.h"
#include "core/Window.h"

namespace DEngine {
    class EditorScene: public Scene{
    public:
        EditorScene(std::shared_ptr<Window> _windowPtr);
        ~EditorScene();
        void beginGUI();
        void endGUI();
        void attach() override;
        void detach()override;
        void input(Event& e)override;
        void update()override;
    private:
        std::shared_ptr<Window> windowPtr;
    };
}
#endif
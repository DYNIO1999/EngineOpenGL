#ifndef DENGINE_ENGINE_H
#define DENGINE_ENGINE_H
#include <functional>

#include <memory>
#include "Window.h"
#include "SceneManager.h"


#include "ecs/EntitySystemManager.h"
#include "systems/PhysicsSystem.h"
#include "systems/ParticleSystem.h"

namespace  DEngine {
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
    class EditorScene;

    class Engine {
    public:
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        bool windowClose(WindowCloseEvent& e);
        void input(Event& e);
        static bool isRunning;
        void run();
        Engine();
        ~Engine();
        std::shared_ptr<Window> window;

        static SceneManager sceneManager;
        static EntitySystemManager entitySystemManager;

    private:
        float deltaTime;
        float lastFrameTime;
        EditorScene* editorScenePtr;
        std::vector<Entity> entities;
    };

}
#endif
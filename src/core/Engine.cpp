#include "Engine.h"

namespace DEngine{
    SceneManager Engine::sceneManager;
    Engine::Engine() {
        WindowData testData{"DEngine", 1600,900};
        window  = std::make_unique<Window>(testData);
        isRunning = true;
        window->setEventCallback(BIND_EVENT_FUNCTION(Engine::input));
        LogManager::init();
    }
    Engine::~Engine() {

    }
    void Engine::run() {

        while(isRunning){
            for (Scene* it: sceneManager) {
                it->update();
            }
            window->Update();
        }
    }
    void Engine::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Engine::windowClose));
        for (auto it = sceneManager.end(); it != sceneManager.begin();) {
            (*it)->input(e);
            if(e.handled){
                break;
            }
            it--;
        }
    }

    bool Engine::windowClose(WindowCloseEvent &e) {
        isRunning = false;
        return true;
    }
}
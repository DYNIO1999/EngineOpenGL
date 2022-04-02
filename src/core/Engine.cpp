#include "Engine.h"


namespace DEngine{

    Engine::Engine() {
        WindowData testData{"DEngine", 1600,900};
        window  = std::make_unique<Window>(testData);
        isRunning = true;
        window->setEventCallback(BIND_EVENT_FUNCTION(Engine::input));
    }
    Engine::~Engine() {

    }
    void Engine::run() {
        while(isRunning){
            window->Update();
        }
    }
    void Engine::input(Event &e) {
        std::cout<<e.getName()<<'\n';
    }
}
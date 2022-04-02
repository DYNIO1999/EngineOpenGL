#include "Engine.h"


namespace DEngine{

    Engine::Engine() {
        WindowData testData{"DEngine", 1600,900};
        window  = std::make_unique<Window>(testData);
        isRunning = true;
    }
    Engine::~Engine() {

    }

    void Engine::run() {


        while(isRunning){
            window->Update();
        }
    }

}
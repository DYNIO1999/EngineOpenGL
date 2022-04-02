#ifndef DENGINE_ENGINE_H
#define DENGINE_ENGINE_H
#include <memory>
#include "Window.h"
namespace  DEngine {
    class Engine {
    public:

        bool isRunning = true;
        void run();
        Engine();
        ~Engine();
        std::unique_ptr<Window> window;
    private:
    };
}
#endif
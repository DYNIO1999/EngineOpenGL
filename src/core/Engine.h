#ifndef DENGINE_ENGINE_H
#define DENGINE_ENGINE_H
#include <functional>

#include <memory>
#include "Window.h"

namespace  DEngine {
#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)
    class Engine {
    public:
        bool windowClose(WindowCloseEvent& e);
        void input(Event& e);
        void update();
        bool isRunning = true;
        void run();
        Engine();
        ~Engine();
        std::unique_ptr<Window> window;
    private:
    };
}
#endif
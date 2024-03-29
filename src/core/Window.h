#ifndef DENGINE_WINDOW_H
#define DENGINE_WINDOW_H
#include <cassert>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "LogManager.h"

#include "events/KeyEvents.h"
#include "events/EngineEvents.h"
#include "events/MouseEvents.h"

namespace DEngine {

    using EventCallbackFunction = std::function<void(Event&)>;

    struct WindowData{

        WindowData(const std::string& _title, int _width, int _height):
        windowTitle(_title),
        width(_width),
        height(_height)
        {
        }
        std::string windowTitle;
        int width;
        int height;
        EventCallbackFunction eventCallback;
    };

    class Window {
    public:
        Window(const WindowData& _data);
        ~Window();
        void setEventCallback(const EventCallbackFunction& _callback);
        int getWidth() const;
        int getHeight() const;
        void setVSync(bool _on);
        void Update();
        GLFWwindow* getGLFWWindow(){return  (window!= nullptr) ? window : nullptr;}
        static GLFWwindow* window;
    private:
        void initGLAD();
        void init();
        void cleanUp();
        WindowData windowData;
    };
}
#endif
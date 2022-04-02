#include "Window.h"

namespace  DEngine {
    Window::Window(const WindowData &_data): windowData(_data) {

        init();
    }
    Window::~Window() {
        cleanUp();
    }

    void Window::init() {
        auto check  = glfwInit();
        assert(check==GLFW_TRUE && "Couldn't initialize GLFW!\n");
        window = glfwCreateWindow(windowData.width, windowData.height, windowData.windowTitle.c_str(), nullptr, nullptr);
        assert(window!= nullptr && "Couldn't createWindow GLFW!\n");
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window,&windowData);
    }

    void Window::cleanUp() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    int Window::getHeight() const {
        return  windowData.height;
    }

    int Window::getWidth() const {
        return  windowData.width;
    }

    void Window::Update() {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    void Window::setEventCallback(const EventCallbackFunction &_callback) {
        windowData.eventCallback = _callback;
    }
}
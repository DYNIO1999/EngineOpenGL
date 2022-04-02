#include "Window.h"

namespace  DEngine {

    static void glfwErrorCallback(int error, const char* description)
    {
        std::cout<<"ERROR: "<<error<<" "<<description;
    }

    Window::Window(const WindowData &_data): windowData(_data) {

        init();
    }
    Window::~Window() {
        cleanUp();
    }

    void Window::init() {
        auto check  = glfwInit();
        assert(check==GLFW_TRUE && "Couldn't initialize GLFW!\n");
        glfwSetErrorCallback(glfwErrorCallback);

        window = glfwCreateWindow(windowData.width, windowData.height, windowData.windowTitle.c_str(), nullptr, nullptr);
        assert(window!= nullptr && "Couldn't createWindow GLFW!\n");
        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window,&windowData);

        glfwSetWindowSizeCallback(window,[](GLFWwindow *window, int width, int height)
                                  {
                                        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                                        data.width = width;
                                        data.height = height;
                                        WindowResizeEvent event(width,height);
                                        data.eventCallback(event);
                                  }
        );
        glfwSetWindowCloseCallback(window,[](GLFWwindow* window){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });
        glfwSetKeyCallback(window,[](GLFWwindow* window, int key,int scancode, int action, int mode){
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS:{
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:{
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:{
                    KeyPressedEvent event(key,1);
                    data.eventCallback(event);
                    break;
                }
            }
        });
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
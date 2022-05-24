#include "Input.h"
#include "core/Window.h"


namespace DEngine{
    bool Input::isKeyPressed(int keycode)
    {
        auto &window = Window::window;
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(int button)
    {
        auto &window = Window::window;
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float Input::getMouseX()
    {
        auto [x, y] = getMousePosition();
        return (float)x;
    }

    float Input::getMouseY()
    {
        auto [x, y] = getMousePosition();
        return (float)y;
    }

    std::pair<float, float> Input::getMousePosition()
    {
        auto &window = Window::window;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return {(float)x, (float)y};
    }
}
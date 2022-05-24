#ifndef DENGINE_INPUT_H
#define DENGINE_INPUT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <utility>

namespace DEngine {
    class Input {
    public:
        static bool isKeyPressed(int keycode);
        static bool isMouseButtonPressed(int button);
        static float getMouseX();
        static float getMouseY();
        static std::pair<float, float> getMousePosition();
    };
}
#endif

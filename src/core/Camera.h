#ifndef DENGINE_CAMERA_H
#define DENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <vector>


namespace DEngine {


    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 5.0f;
    const float SENSITIVITY = 100.0f;
    const float ZOOM = 45.0f;

    enum class Camera_Movement
    {
        FORWARD_CAMERA_MOVE,
        BACKWARD_CAMERA_MOVE,
        LEFT_CAMERA_MOVE,
        RIGHT_CAMERA_MOVE
    };

    class Camera {
    public:
        float yaw;
        float pitch;
        float movementSpeed;
        float mouseSensitivity;
        float zoom;

        glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        inline glm::mat4 GetViewMatrix() const
        {
            return glm::lookAt(position, position + front, up);
        }
        Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH):
                front(glm::vec3(0.0f, 0.0f, -1.0f)),
                movementSpeed(SPEED),
                mouseSensitivity(SENSITIVITY),
                zoom(ZOOM)
        {
            position = _position;
            worldUp = _up;
            yaw = _yaw;
            pitch = _pitch;
            updateCamera();
        }
        ~Camera(){

        }
        void processKeyboard(Camera_Movement direction, float deltaTime);
        void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void processMouseScroll(float yoffset);

    private:
        void updateCamera();
    };
}
#endif
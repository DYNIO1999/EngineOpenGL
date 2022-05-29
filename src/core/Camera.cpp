#include "Camera.h"


namespace DEngine{

    void Camera::processKeyboard(Camera_Movement direction, float deltaTime){
        float velocity = movementSpeed * deltaTime;
        if (direction == Camera_Movement::FORWARD_CAMERA_MOVE)
            position += front * velocity;
        if (direction == Camera_Movement::BACKWARD_CAMERA_MOVE)
            position -= front * velocity;
        if (direction == Camera_Movement::LEFT_CAMERA_MOVE)
            position -= right * velocity;
        if (direction == Camera_Movement::RIGHT_CAMERA_MOVE)
            position += right * velocity;
    }
    void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch){
        float rotX = mouseSensitivity * xoffset;
        float rotY = mouseSensitivity * yoffset;
        glm::vec3 newOrientation = glm::rotate(front, glm::radians(-rotX), glm::normalize(glm::cross(front, up)));
        if (std::abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {

            front = newOrientation;
        }
        front = glm::rotate(front, glm::radians(-rotY), up);
        updateCamera();
    }
    void Camera::processMouseScroll(float yoffset){
        zoom -= (float)yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;
    }
    void Camera::updateCamera(){
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
}
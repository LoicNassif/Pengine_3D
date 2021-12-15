#pragma once

#include <glad/glad.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include <vector>

// Camera directions
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// default camera values
const float YAW             = -90.0f;
const float PITCH           = 0.0f;
const float SPEED           = 4.0f;
const float SCROLL_SPEED    = 1.5f;
const float SENSITIVITY     = 0.1f;
const float FOV             = 45.0f;

class Camera {
public:
    // Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler Angles
    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float ScrollSensitivity;
    float Fov;

    // Vector constructor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
            float yaw = YAW, float pitch = PITCH) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), 
        Fov(FOV), ScrollSensitivity(SCROLL_SPEED) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Scalar constructor
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), 
        Fov(FOV), ScrollSensitivity(SCROLL_SPEED) {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // Keyboard input for position changes
    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)   Position += Front * velocity;
        if (direction == BACKWARD)  Position -= Front * velocity;
        if (direction == LEFT)      Position -= Right * velocity;
        if (direction == RIGHT)     Position += Right * velocity;
        if (direction == UP)        Position += Up * velocity;
        if (direction == DOWN)      Position -= Up * velocity;
    }

    // Mouse input for angle changes
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    // Mouse scroll for zoom changes
    void ProcessMouseScroll(float yoffset)
    {
        if (Fov >= 1.0f && Fov <= 55.0f)
            Fov -= yoffset * ScrollSensitivity;
        else if (Fov < 1.0f)
            Fov = 1.0f;
        else if (Fov > 55.0f)
            Fov = 55.0f;
    }

private:
    // Compute front vectors from updated Euler angles
    void updateCameraVectors() {
        // Compute front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // Also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
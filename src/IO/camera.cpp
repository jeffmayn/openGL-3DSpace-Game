//
// Created by chris on 10.12.2017.
//
#include <iostream>

#include "camera.h"
#include "controls.h"
// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
// Constructor with scalar values
Camera::Camera(float xPos, float yPos, float zPos, float xUp, float yUp, float zUp, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(xPos, yPos, zPos);
    WorldUp = glm::vec3(xUp, yUp, zUp);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD) {
        Position += Front * velocity;
    }
    if (direction == BACKWARD) {
        Position -= Front * velocity;
    }
    if (direction == LEFT) {
        Position -= Right * velocity;
    }
    if (direction == RIGHT) {
        Position += Right * velocity;
    }
    if(direction == SPACE){
        //TODO
    }
    if (direction == SHIFT) {
        MovementSpeed = 10.0f + deltaTime;
    }
    else{
        MovementSpeed = 20.0f + deltaTime;
    }
//    Position.y = 0.0f;
}
void Camera::InputMovement(glm::vec3 mP) {
    Position = mP;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float offsetX, float offsetY, GLboolean constrainPitch)
{
    offsetX *= MouseSensitivity;
    offsetY *= MouseSensitivity;

    Yaw   += offsetX;
    Pitch += offsetY;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
//    {
//        if (Pitch > 89.0f)
//            Pitch = 89.0f;
//        if (Pitch < -89.0f)
//            Pitch = -89.0f;
//    }

    // this little guy gives you the power to control a battlecruiser!!
    followMouse(offsetX,offsetY);

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float offsetY)
{
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= offsetY * 2.3f;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
//    glm::vec3 front;
//    front.x = (float) (cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
//    front.y = (float) (sin(glm::radians(Pitch)));
//    front.z = (float) (sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
//    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
}
void Camera::setPos(glm::vec3 pos){
    Position = pos;
}
void Camera::setFront(glm::vec3 front){
    Front = glm::normalize(front);

}

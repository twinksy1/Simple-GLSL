#include "Camera.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect,
               float zNear, float zFar)
{
    perspective = glm::perspective(fov, aspect, zNear, zFar);
    this->pos = pos;
    forward = glm::vec3(0.0, 0.0, 1.0);
    up = glm::vec3(0.0, 1.0, 0.0);
    speed = 0.5f;
    yaw = pitch = 0.0f;
}
glm::mat4 Camera::getViewProjection() const
{
    return perspective * glm::lookAt(pos, pos+forward, up);
}

glm::mat4& Camera::getPerspective()
{
    return perspective;
}
glm::vec3& Camera::getPos()
{
    return pos;
}
glm::vec3& Camera::getForward()
{
    return forward;
}
glm::vec3& Camera::getUp()
{
    return up;
}
float& Camera::getSpeed()
{
    return speed;
}
float& Camera::getPitch()
{
    return pitch;
}
float& Camera::getYaw()
{
    return yaw;
}

void Camera::setPerspective(const glm::mat4 p)
{
    perspective = p;
}
void Camera::setPos(const glm::vec3 p)
{
    pos = p;
}
void Camera::setForward(const glm::vec3 f)
{
    forward = f;
}
void Camera::setUp(const glm::vec3 u)
{
    up = u;
}
void Camera::setSpeed(float s)
{
    speed = s;
}

void Camera::calcFront(float xoff, float yoff)
{
    yaw += xoff;
    pitch += yoff;

    if(pitch > 89.0f) {
        pitch = 89.0f;
    }
    if(pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(direction);
}
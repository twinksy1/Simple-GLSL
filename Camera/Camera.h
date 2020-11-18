#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Camera {
    private:
    glm::mat4 perspective;
    glm::vec3 pos;
    // What direction is forward
    glm::vec3 forward;
    // What direction is up
    glm::vec3 up;
    float speed;
    float pitch;
    float yaw;

    public:
    Camera(const glm::vec3&, float, float, float, float);

    glm::mat4 getViewProjection() const;

    glm::mat4& getPerspective();
    glm::vec3& getPos();
    glm::vec3& getForward();
    glm::vec3& getUp();
    float& getSpeed();
    float& getPitch();
    float& getYaw();

    void setPerspective(const glm::mat4);
    void setPos(const glm::vec3);
    void setForward(const glm::vec3);
    void setUp(const glm::vec3);
    void setSpeed(float);

    void calcFront(float, float);
};

#endif
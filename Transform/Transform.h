#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Transform {
    private:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

    public:
    Transform();
    Transform(const glm::vec3&, const glm::vec3&,
             const glm::vec3&);
    
    glm::vec3& getPos();
    glm::vec3& getRot();
    glm::vec3& getScale();

    void setPos(const glm::vec3);
    void setRot(const glm::vec3);
    void setScale(const glm::vec3);

    glm::mat4 getModel() const;
};

#endif
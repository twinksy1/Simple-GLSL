#include "Transform.h"

Transform::Transform()
{
    this->pos = glm::vec3();
    this->rot = glm::vec3();
    this->scale = glm::vec3(1.0, 1.0, 1.0);
}
Transform::Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(),
                     const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0))
{
    this->pos = pos;
    this->rot = rot;
    this->scale = scale;
}

glm::vec3& Transform::getPos()
{
    return pos;
}

glm::vec3& Transform::getRot()
{
    return rot;
}

glm::vec3& Transform::getScale()
{
    return scale;
}

void Transform::setPos(const glm::vec3 p)
{
    pos = p;
}
void Transform::setRot(const glm::vec3 r)
{
    rot = r;
}
void Transform::setScale(const glm::vec3 s)
{
    scale = s;
}

glm::mat4 Transform::getModel() const
{
    glm::mat4 posMatrix = glm::translate(pos);

    glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1.0,0.0,0.0));
    glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0.0,1.0,0.0));
    glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0.0,0.0,1.0));
    // Write them out in the opposite order you want them applied
    glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

    glm::mat4 scaleMatrix = glm::scale(scale);

    return posMatrix * rotMatrix * scaleMatrix;
}
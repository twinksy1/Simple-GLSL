#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "./../Obj_Loader/Obj_Loader.h"

class Vertex {
    private:
    glm::vec3 pos;
    glm::vec2 texCoord;
    glm::vec3 normal;

    public:
    Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
    {
        this->pos = pos;
        this->texCoord = texCoord;
        this->normal = normal;
    }
    Vertex(const glm::vec3& pos)
    {
        this->pos = pos;
    }
    inline glm::vec3* getPos() { return &pos; }
    inline glm::vec2* getTexCoord() { return &texCoord; }
    inline glm::vec3* getNormal() { return &normal; }
};

class Mesh {
    private:
    Mesh(const Mesh& other) {}
    void operator=(const Mesh& other) {}
    void initMesh(const IndexedModel&);

    enum
    {
        POSITION_VB,
        TEXCOORD_VB,
        INDEX_VB,
        NORMAL_VB,
        NUM_BUFFERS
    };

    GLuint VAO;
    GLuint VBO[NUM_BUFFERS];
    unsigned int drawCount;

    public:
    Mesh(Vertex*, unsigned int, unsigned int*, unsigned int);
    Mesh(const std::string&);
    virtual ~Mesh();

    void draw();
};

#endif
#include "Mesh.h"
#include <vector>
#include <iostream>
#include <string>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;

    for(unsigned int i=0; i<numVertices; i++) {
        model.positions.push_back(*vertices[i].getPos());
        model.texCoords.push_back(*vertices[i].getTexCoord());
        model.normals.push_back(*vertices[i].getNormal());
    }

    for(unsigned int i=0; i<numIndices; i++) {
        model.indices.push_back(indices[i]);
    }
    initMesh(model);
}

Mesh::Mesh(const std::string& filename)
{
    IndexedModel model = OBJModel(filename).ToIndexedModel();
    initMesh(model);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw()
{
    glBindVertexArray(VAO);

    //glDrawArrays(GL_TRIANGLES, 0, drawCount);
    glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel& model)
{
    drawCount = model.indices.size();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(NUM_BUFFERS, VBO);

    // Positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
    // Put vertex data into buffer
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Texture Coordinates
    glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXCOORD_VB]);
    // Put vertex data into buffer
    glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Normals
    glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_VB]);
    // Put vertex data into buffer
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_VB]);
    // Put vertex data into buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); 

    glBindVertexArray(0);
}
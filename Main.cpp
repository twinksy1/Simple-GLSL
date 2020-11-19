#include <iostream>
#include "./Display/Display.h"
// Shader.h already includes Transform.h & Camera.h
#include "./Shader/Shader.h"
#include "./Mesh/Mesh.h"
#include "./Texture/Texture.h"

#define DEG2RAD 3.14159/180.0

int main()
{
    Display display(3000, 2000, "Name");
    Shader shader("./Shader_Programs/basicShader");
    Shader shader2("./Shader_Programs/Shad1");
    Texture texture("./Images/monkey.png");
    Camera cam(glm::vec3(0.0,0.0,-3.0),70.0f,(float)display.getXres()/(float)display.getYres(),
               0.01f, 1000.0f);
    Transform transform;
    Transform transform2;

    Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0.0)),
                          Vertex(glm::vec3(0.0,0.5,0.0)),
                          Vertex(glm::vec3(0.5,-0.5,0.0))
                        };
    unsigned int indices[] = {0, 1, 2};
    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    
    Mesh mesh2("Sample_Mesh.obj");

    float counter = 0.0f;

    while(!display.getIsClosed()) {
        display.clear(1.0f, 1.0f, 0.0f, 1.0f);

        transform.getPos().x = sinf(counter*DEG2RAD);
        //cam.getPos().z = cosf(counter*DEG2RAD) * -3.0f;
        //transform.getRot().z = counter*DEG2RAD;
        //float newScale = cosf(counter*DEG2RAD);
        //transform.setScale(glm::vec3(newScale, newScale, newScale));

        shader.bind();
        shader.update(transform, cam);
        texture.bind(0);
        mesh2.draw();

        shader2.bind();
        shader2.update(transform2, cam);
        mesh.draw();
        display.update(cam);

        counter += 0.5f;
    }
    return 0;
}
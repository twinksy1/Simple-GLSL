#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "./../Transform/Transform.h"
#include "./../Camera/Camera.h"

class Shader {
    private:
    Shader(const Shader& other) {}
    void operator=(const Shader& other) {}

    static const unsigned int NUM_SHADERS = 2;

    enum
    {
        TRANSFORM_U,
        NUM_UNIFORMS
    };

    GLuint program;
    GLuint shaders[NUM_SHADERS];
    GLuint uniforms[NUM_UNIFORMS];

    public:
    Shader(const std::string&);
    virtual ~Shader();
    void bind();
    void update(const Transform&, const Camera&);
};

#endif
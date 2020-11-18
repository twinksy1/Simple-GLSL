#include "Shader.h"
#include <iostream>
#include <fstream>

static void checkShaderError(GLuint, GLuint, bool, const std::string&);
static std::string loadShader(const std::string&);
static GLuint createShader(const std::string&, GLenum);

Shader::Shader(const std::string& fileName)
{
    program = glCreateProgram();
    shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i=0; i<NUM_SHADERS; i++)
        glAttachShader(program, shaders[i]);
    
    // Defining attributes used in shaders
    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "texCoord");
    glBindAttribLocation(program, 2, "normal");
    
    glLinkProgram(program);
    checkShaderError(program, GL_LINK_STATUS, true, "Error program failed to link: ");

    glValidateProgram(program);
    checkShaderError(program, GL_VALIDATE_STATUS, true, "Error program is invalid: ");

    // Allowing access to transform uniform variable in vertex shader
    uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

Shader::~Shader()
{
    std::cout << "Deleting shaders\n";
    for(unsigned int i=0; i<NUM_SHADERS; i++) {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    std::cout << "Deleting shader program\n";
    glDeleteProgram(program);
}

void Shader::bind()
{
    glUseProgram(program);
}

static GLuint createShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0) {
        std::cerr << "Error: shader creation failed\n";
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader: ");


    return shader;
}

static std::string loadShader(const std::string& fileName)
{
    std::ifstream file;
    std::cout << "Loading " << fileName << std::endl;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open()) {
        while(file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errMessage)
{
    GLint success = 0;
    GLchar error[1024] = {0};

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE) {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errMessage << ": '" << error << "'" << std::endl;
    }
}

void Shader::update(const Transform& t, const Camera& c)
{
    glm::mat4 model = c.getViewProjection() * t.getModel();

    glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

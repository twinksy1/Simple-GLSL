#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>


class Texture {
    private:
    Texture(const Texture& other) {}
    void operator=(const Texture& other) {}

    GLuint tID;

    public:
    Texture(const std::string&);
    virtual ~Texture();

    void bind(unsigned int);
};

#endif
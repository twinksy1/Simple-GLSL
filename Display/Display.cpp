#include "Display.h"
#include "HandleInputs.h"
#include <iostream>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    // Creating depth/z buffer: solution to drawing things in back to front
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                width, height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);

    GLenum status = glewInit();
    if(status != GLEW_OK) {
        std::cerr << "Error initializing glew\n";
    }

    xres = width;
    yres = height;
    isClosed = false;

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    // Trap mouse in window
    SDL_SetRelativeMouseMode(SDL_TRUE);

    std::cout << "Constructed window\n";
}
Display::~Display()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Closed window\n";
}

bool Display::getIsClosed()
{
    return isClosed;
}

void Display::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update(Camera& cam)
{
    // Swap buffer
    SDL_GL_SwapWindow(window);

    // Handling of events
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            isClosed = true;
        } else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            if(keyboardInput(e, cam)) {
                isClosed = true;
            }
        }
        checkMouse(e, cam);
    }
}

int Display::getXres() const
{
    return xres;
}

int Display::getYres() const
{
    return yres;
}
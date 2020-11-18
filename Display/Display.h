#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string>
#include "./../Camera/Camera.h"

class Display {
    private:
    SDL_Window* window;
    SDL_GLContext glContext;
    Display(const Display& other) {}
    void operator=(const Display& other) {}
    bool isClosed = false;
    int xres, yres;
    
    public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void update(Camera&);
    bool getIsClosed();
    void clear(float, float, float, float);

    int getXres() const;
    int getYres() const;
};

#endif
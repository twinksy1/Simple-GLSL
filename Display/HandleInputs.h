#ifndef HANDLEINPUTS_H
#define HANDLEINPUTS_H

#include "Display.h"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <iostream>

void checkMouse(SDL_Event e, Camera& cam)
{
    static int mousex, mousey;
    const float sensitivity = 0.1f;
    static bool lbutton_down = false, rbutton_down = false;

    if (e.type == SDL_MOUSEMOTION) {
        // Mouse moved
        SDL_GetMouseState(&mousex, &mousey);
        // e.motion.yrel for inverted controls
        cam.calcFront(e.motion.xrel*sensitivity, -e.motion.yrel*sensitivity);
    }

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        // Mouse click
        if (e.button.button == SDL_BUTTON_LEFT) {
        }
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        // Button release
        lbutton_down = false;
        rbutton_down = false;
    }
}

bool keyboardInput(SDL_Event e, Camera& cam)
{
    static bool shift_down = false;
    // Key up
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_LSHIFT:
            shift_down = false;
            //printf("Shift key released\n");
            break;
        }
    }
    // Handle keyboard input
    switch (e.key.keysym.sym) {
        case SDLK_LSHIFT:
            shift_down = true;
            break;
        case SDLK_a:
            cam.getPos() -= glm::normalize(glm::cross(cam.getForward(), cam.getUp())) * cam.getSpeed();
            // std::cout << cam.getPos().x << " " << cam.getPos().y << " "
            //         << cam.getPos().z << std::endl;
            break;
        case SDLK_d:
            cam.getPos() += glm::normalize(glm::cross(cam.getForward(), cam.getUp())) * cam.getSpeed();
            // std::cout << cam.getPos().x << " " << cam.getPos().y << " "
            //         << cam.getPos().z << std::endl;
            break;
        case SDLK_w: 
            cam.getPos() += cam.getForward() * cam.getSpeed();
            // std::cout << cam.getPos().x << " " << cam.getPos().y << " "
            //         << cam.getPos().z << std::endl;
            break;
        case SDLK_s: 
            cam.getPos() -= cam.getForward() * cam.getSpeed();
            // std::cout << cam.getPos().x << " " << cam.getPos().y << " "
            //         << cam.getPos().z << std::endl;
            break;
        case SDLK_ESCAPE:
            return true;
            break;
    }
    return false;
}

#endif
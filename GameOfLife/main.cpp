#include <cmath>
#include <SDL.h>
#include "view.h"
#include "model.h"


int main(int argc, char *args[])
{
    Model model;
    View view(&model);

    //Main loop flag
    bool quit = false;
    bool paused = false;
    int stepSpeed = 500;
    int startTicks = SDL_GetTicks();

    //Event handler
    SDL_Event e;

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_c) {
                    view.toggleColored();
                }
                if (e.key.keysym.sym == SDLK_p) {
                    paused = !paused;
                }
                if (e.key.keysym.sym == SDLK_s) {
                    (*view.getModel()).seedLife();
                }
                if (e.key.keysym.sym == SDLK_r) {
                    (*view.getModel()).seedLifeRand();
                }
                if (e.key.keysym.sym == SDLK_KP_PLUS) {
                    stepSpeed = std::max(10, stepSpeed - 100);
                }
                if (e.key.keysym.sym == SDLK_KP_MINUS) {
                    stepSpeed +=100;
                }
                if (e.key.keysym.sym == SDLK_SPACE) {
                    if (paused)
                        (*view.getModel()).calculateNextGeneration();
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    (*view.getModel()).reset();
                    stepSpeed = 500;
                }
            }
        }

        if (!paused && SDL_GetTicks() - startTicks > stepSpeed) {
            (*view.getModel()).calculateNextGeneration();
            startTicks = SDL_GetTicks();
        }

        //Clear screen
        SDL_SetRenderDrawColor(view.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(view.getRenderer());

        view.drawGeneration();
        view.drawText();

        //Update screen
        SDL_RenderPresent(view.getRenderer());
    }

    //Free resources and close SDL
    view.close();

    return 0;
}
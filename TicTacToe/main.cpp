#include <SDL.h>
#include "view.h"
#include "model.h"




int main(int argc, char *args[])
{
    Model model;
    View view(model);

    //Main loop flag
    bool quit = false;
    bool gameEnded = false;

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
                if (e.key.keysym.sym == SDLK_UP) {
                    (*view.getModel()).movePrompt(0);
                }
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    (*view.getModel()).movePrompt(1);
                }
                if (e.key.keysym.sym == SDLK_DOWN) {
                    (*view.getModel()).movePrompt(2);
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    (*view.getModel()).movePrompt(3);
                }
                if (e.key.keysym.sym == SDLK_SPACE && !gameEnded) {
                    gameEnded = (*view.getModel()).markSquare();
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    (*view.getModel()).reset();
                    gameEnded = false;
                }
            }
        }

        //Clear screen

        SDL_SetRenderDrawColor(view.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(view.getRenderer());


        view.drawField();
        view.drawPrompt();
        view.drawMatch();

        //Update screen
        SDL_RenderPresent(view.getRenderer());
    }

    //Free resources and close SDL
    view.close();

    return 0;
}
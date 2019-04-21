//
// Created by zbora on 2019-04-21.
//

#include <iostream>
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "view.h"
#include "model.h"


View::View(Model &model)
{
    this->model = model;
    //Start up SDL and create window
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
        close();
    }
    verticalStep = SCREEN_HEIGHT / (double) model.getMapHeight();
    horizontalStep = SCREEN_WIDTH / (double) model.getMapWidth();
}

SDL_Renderer *View::getRenderer()
{
    return gRenderer;
}

Model *View::getModel()
{
    return &model;
}

void View::drawField()
{
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    //Horizontal lines
    for (double i = 0; i < SCREEN_HEIGHT; i += verticalStep) {
        SDL_RenderDrawLine(gRenderer, 0, i, SCREEN_WIDTH, i);
    }
    //Vertical lines
    for (double i = 0; i < SCREEN_WIDTH; i += horizontalStep) {
        SDL_RenderDrawLine(gRenderer, i, 0, i, SCREEN_HEIGHT);
    }
}

void View::drawPrompt()
{
    std::pair<int, int> tempPos = model.getPromptPos();
    if (model.getCurrentPlayer() == 1)
        SDL_SetRenderDrawColor(gRenderer, 43, 255, 82, 255);
    else
        SDL_SetRenderDrawColor(gRenderer, 226, 31, 13, 255);
    SDL_Rect rectangle = {tempPos.second * horizontalStep, tempPos.first * verticalStep, horizontalStep, verticalStep};
    SDL_RenderFillRect(gRenderer, &rectangle);

}

void View::markSquare(double yPos, double xPos, int player)
{
    if (player == 1) {
        circleRGBA(gRenderer, xPos + horizontalStep / 2, yPos + verticalStep / 2,
                   (verticalStep > horizontalStep ? horizontalStep : verticalStep) / 2, 43, 255, 82, 255);
    } else {
        SDL_SetRenderDrawColor(gRenderer, 226, 31, 13, 255);
        SDL_RenderDrawLine(gRenderer, xPos, yPos, xPos + horizontalStep, yPos + verticalStep);
        SDL_RenderDrawLine(gRenderer, xPos, yPos + verticalStep, xPos + horizontalStep, yPos);
    }
}

void View::drawMatch()
{
    for (int i = 0; i < model.getMapHeight(); ++i) {
        for (int j = 0; j < model.getMapWidth(); ++j) {
            if (model.getPosValue(i, j) == 1) {
                markSquare(i * verticalStep, j * horizontalStep, 1);
            }
            if (model.getPosValue(i, j) == -1) {
                markSquare(i * verticalStep, j * horizontalStep, -1);
            }
        }
    }
}

bool View::init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void View::close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();
}


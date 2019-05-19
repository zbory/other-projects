//
// Created by zbora on 2019-04-21.
//

#include <iostream>
#include <SDL.h>
#include "view.h"
#include "model.h"


View::View(Model *model)
{
    this->model = model;
    //Start up SDL and create window
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
        close();
    }
    loadMedia();
    verticalStep = SCREEN_HEIGHT / (double) model->getMapHeight();
    horizontalStep = SCREEN_WIDTH / (double) model->getMapWidth();
    isColored = false;
}

SDL_Renderer *View::getRenderer()
{
    return gRenderer;
}

Model *View::getModel()
{
    return model;
}

void View::toggleColored()
{
    isColored = !isColored;
}

void View::drawCell(double yPos, double xPos, int player)
{
    SDL_Rect rect = {xPos, yPos, horizontalStep, verticalStep};
    if (player == 1) {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderFillRect(gRenderer, &rect);
    }
}

void View::drawGeneration()
{
    for (int i = 0; i < model->getMapHeight(); ++i) {
        for (int j = 0; j < model->getMapWidth(); ++j) {
            if (model->getPosValue(i, j) == 1) {
                drawCell(i * verticalStep, j * horizontalStep, 1);
            }
            if (model->getPosValue(i, j) == 0) {
                drawCell(i * verticalStep, j * horizontalStep, 0);
            }
        }
    }
}

void View::drawText()
{
    SDL_Rect temp = {SCREEN_WIDTH - 200, 0, 200, 50};
    SDL_Color color = {0, 0, 0, 255};
    std::string generation = "Generation: " + std::to_string(model->getGenerationCount());
    generationText = loadFromRenderedText(generation, color, generationText);
    SDL_RenderCopy(gRenderer, generationText, NULL, &temp);
}

bool View::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    font = TTF_OpenFont("visitor1.ttf", 14);
    if (font == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }


    return success;
}

SDL_Texture *View::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Texture *textTexture)
{
    //Get rid of preexisting texture
    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = NULL;
    }


    //Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        //Create texture from surface pixels
        textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (textTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return textTexture;
}

bool View::init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
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

    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void View::close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    TTF_Quit();
    SDL_Quit();
}


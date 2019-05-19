//
// Created by zbora on 2019-04-21.
//

#ifndef TICTACTOE_VIEW_H
#define TICTACTOE_VIEW_H

#include <iostream>
#include <SDL_ttf.h>
#include "model.h"

class View {
public:
    View(Model *model);

//Returns the renderer object
    SDL_Renderer *getRenderer();

//Returns the model object
    Model *getModel();

//Enable colored generations
    void toggleColored();

//Draws X or O at prompt
    void drawCell(double yPos, double xPos, int player);

//Draw match state
    void drawGeneration();

//Draw generation text
    void drawText();

//Load font
    bool loadMedia();

//Create text texture
    SDL_Texture *loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Texture *textTexture);

//Starts up SDL and creates window
    bool init();

//Frees media and shuts down SDL
    void close();

private:
    //Screen dimension constants
    Model *model;
    const int SCREEN_WIDTH = 1050;
    const int SCREEN_HEIGHT = 650;
    double verticalStep;
    double horizontalStep;
    bool isColored;
    //The window we'll be rendering to
    SDL_Window *gWindow = nullptr;
    //The window renderer
    SDL_Renderer *gRenderer = nullptr;
    SDL_Texture *generationText = nullptr;
    TTF_Font *font;
};


#endif //TICTACTOE_VIEW_H

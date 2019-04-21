//
// Created by zbora on 2019-04-21.
//

#ifndef TICTACTOE_VIEW_H
#define TICTACTOE_VIEW_H

#include <iostream>
#include "model.h"

class View {
public:
    View(Model &model);

//Returns the renderer object
    SDL_Renderer *getRenderer();

//Returns the model object
    Model *getModel();

//Draws playing field
    void drawField();

//Draws player prompt
    void drawPrompt();

//Draws X or O at prompt
    void markSquare(double yPos, double xPos, int player);

//Draw match state
    void drawMatch();

//Starts up SDL and creates window
    bool init();

//Frees media and shuts down SDL
    void close();

private:
    //Screen dimension constants
    Model model;
    const int SCREEN_WIDTH = 1050;
    const int SCREEN_HEIGHT = 660;
    double verticalStep;
    double horizontalStep;
    //The window we'll be rendering to
    SDL_Window *gWindow = nullptr;
    //The window renderer
    SDL_Renderer *gRenderer = nullptr;
};


#endif //TICTACTOE_VIEW_H

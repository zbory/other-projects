//
// Created by zbora on 2019-05-07.
//

#include <iostream>
#include "colorLookupTable.h"

ColorLookupTable::ColorLookupTable()
{
    //Fill color lookup table
    for (int k = 0; k < levels; ++k) {
        SDL_Color *temp = new SDL_Color();
        temp->r = color.r;
        temp->g = color.g;
        temp->b = color.b;
        temp->a = color.a;
        color.a -= 255 / levels;
        colorTable.push_back(temp);
        changeColor(state, color, colorStep);
    }
}

ColorLookupTable::~ColorLookupTable()
{
    for (int i = 0; i < colorTable.size(); ++i) {
        delete colorTable[i];
        colorTable[i] = nullptr;
    }
}

uint32_t ColorLookupTable::getColorValue(int index)
{

    return colorTable[index]->b + (colorTable[index]->g << 8)
           + (colorTable[index]->r << 16); // + (colorTable[index]->a << 24);
}

int ColorLookupTable::getTableSize()
{
    return colorTable.size();
}

void ColorLookupTable::changeColor(State &state, SDL_Color &color, int colorStep)
{

    switch (state) {
    case INCGREEN:
        color.g += colorStep;
        if (color.g == 255)
            state = DECRED;
        break;
    case DECRED:
        color.r -= colorStep;
        if (color.r == 0)
            state = INCBLUE;
        break;
    case INCBLUE:
        color.b += colorStep;
        if (color.b == 255)
            state = DECGREEN;
        break;
    case DECGREEN:
        color.g -= colorStep;
        if (color.g == 0)
            state = INCRED;
        break;
    case INCRED:
        color.r += colorStep;
        if (color.r == 255)
            state = DECBLUE;
        break;
    case DECBLUE:
        color.b -= colorStep;
        if (color.b == 0)
            state = INCGREEN;
        break;
    default:
        break;
    }
}
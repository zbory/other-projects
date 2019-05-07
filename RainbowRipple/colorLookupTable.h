//
// Created by zbora on 2019-05-07.
//

#ifndef RAINBOWRIPPLE_COLORLOOKUPTABLE_H
#define RAINBOWRIPPLE_COLORLOOKUPTABLE_H

#include <vector>
#include <SDL.h>

enum State {
    INCRED,
    INCGREEN,
    INCBLUE,
    DECRED,
    DECGREEN,
    DECBLUE
};

class ColorLookupTable {
public:
    ColorLookupTable();
    ~ColorLookupTable();

    uint32_t getColorValue(int index);

    int getTableSize();

private:
    SDL_Color color = {255, 0, 0, 255};
    State state = INCGREEN;
    int colorStep = 1;
    int levels = 1530 / colorStep;


    std::vector<SDL_Color *> colorTable;

    void changeColor(State &state, SDL_Color &color, int colorStep);

};


#endif //RAINBOWRIPPLE_COLORLOOKUPTABLE_H

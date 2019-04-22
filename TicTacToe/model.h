//
// Created by zbora on 2019-04-21.
//

#ifndef MULTIPLAYERTICTACTOE_MODEL_H
#define MULTIPLAYERTICTACTOE_MODEL_H

#include <vector>

const int MAP_WIDTH = 35;
const int MAP_HEIGHT = 22;
const int VICTORY = 5;


class Model {
public:
    Model();

    int getMapWidth();

    int getMapHeight();

    std::pair<int, int> getPromptPos();

    int getCurrentPlayer();

    int getPosValue(int y, int x);

    bool markSquare();

    //0 - UP, 1 - RIGHT, 2 - DOWN, 3 - LEFT
    void movePrompt(int direction);

    void reset();
private:
    int mapWidth = MAP_WIDTH;
    int mapHeight = MAP_HEIGHT;
    int victoryCount = VICTORY;
    std::vector<std::vector<int>> field;
    std::pair<int, int> promptPos;
    //-1 - cross, 1 - circle
    int currentPlayer;

    void switchPlayer();

    bool checkWinner();

    bool fiveInARow(int yPos, int xPos);
};


#endif //MULTIPLAYERTICTACTOE_MODEL_H

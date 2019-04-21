//
// Created by zbora on 2019-04-21.
//

#include <iostream>
#include "model.h"

Model::Model()
{
    currentPlayer = -1;
    promptPos = {MAP_HEIGHT / 2, MAP_WIDTH / 2};
/*    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            field[i][j] = 0;
        }
    }*/
    field.resize(mapHeight, std::vector<int>(mapWidth, 0));
}

int Model::getMapWidth()
{
    return mapWidth;
}

int Model::getMapHeight()
{
    return mapHeight;
}

std::pair<int, int> Model::getPromptPos()
{
    return promptPos;
}

int Model::getCurrentPlayer()
{
    return currentPlayer;
}

int Model::getPosValue(int y, int x)
{
    return field[y][x];
}

void Model::switchPlayer()
{
    if (currentPlayer == 1)
        currentPlayer = -1;
    else
        currentPlayer = 1;
}

bool Model::markSquare()
{
    if (field[promptPos.first][promptPos.second] == 0) {
        if (currentPlayer == 1)
            field[promptPos.first][promptPos.second] = 1; // O
        else
            field[promptPos.first][promptPos.second] = -1; // X
        switchPlayer();
    }
    //return checkWinner();
    return false;
}

void Model::movePrompt(int direction)
{
    switch (direction) {
        case 0:
            if (promptPos.first > 0) {
                promptPos = {promptPos.first - 1, promptPos.second};
            }
            break;
        case 1:
            if (promptPos.second < mapWidth - 1) {
                promptPos = {promptPos.first, promptPos.second + 1};
            }
            break;
        case 2:
            if (promptPos.first < mapHeight - 1) {
                promptPos = {promptPos.first + 1, promptPos.second};
            }
            break;
        case 3:
            if (promptPos.second > 0) {
                promptPos = {promptPos.first, promptPos.second - 1};
            }
            break;
        default:
            break;
    }
}

bool Model::checkWinner()
{
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (fiveInARow(i, j)) {
                return true;
            }
        }
    }
    return false;
}

bool Model::fiveInARow(int yPos, int xPos)
{
    bool horizontal = true;
    bool vertical = true;
    bool diagonalf = true;
    bool diagonalb = true;

    if (field[yPos][xPos] != 0) {
        int startSymbol = field[yPos][xPos];

        //Check for horizontal
        for (int i = 0; i < victoryCount; ++i) {
            int nextSymbol;
            try {
                nextSymbol = field.at(yPos).at(xPos + i);
            } catch (std::out_of_range e) {
                std::cout << e.what();
                break;
            }
            if (nextSymbol != startSymbol) {
                horizontal = false;
                break;
            }
        }
        //Check for vertical
        for (int i = 0; i < victoryCount; ++i) {
            int nextSymbol;
            try {
                nextSymbol = field.at(yPos + i).at(xPos);
            } catch (std::out_of_range e) {
                std::cout << e.what();
                break;
            }
            if (nextSymbol != startSymbol) {
                horizontal = false;
                break;
            }
        }
        //Check for diagonal forward
        for (int i = 0; i < victoryCount; ++i) {
            int nextSymbol;
            try {
                nextSymbol = field.at(yPos + i).at(xPos + i);
            } catch (std::out_of_range e) {
                std::cout << e.what();
                break;
            }
            if (nextSymbol != startSymbol) {
                horizontal = false;
                break;
            }
        }
        //Check for diagonal backward
        for (int i = 0; i < victoryCount; ++i) {
            int nextSymbol;
            try {
                nextSymbol = field.at(yPos - i).at(xPos - i);
            } catch (std::out_of_range e) {
                std::cout << e.what();
                break;
            }
            if (nextSymbol != startSymbol) {
                horizontal = false;
                break;
            }
        }
        return horizontal || vertical || diagonalf || diagonalb;
    }
    return false;
}
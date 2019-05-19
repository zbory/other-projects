//
// Created by zbora on 2019-04-21.
//

#include <iostream>
#include <ctime>
#include "model.h"

Model::Model()
{

    generation1.resize(mapHeight, std::vector<int>(mapWidth, 0));
    generation2.resize(mapHeight, std::vector<int>(mapWidth, 0));
    isSeeded = false;
    generationCount = 0;
}

int Model::getMapWidth()
{
    return mapWidth;
}

int Model::getMapHeight()
{
    return mapHeight;
}

int Model::getPosValue(int y, int x)
{
    return generation1[y][x];
}

int Model::getGenerationCount()
{
    return generationCount;
}

void Model::seedLife()
{
    isSeeded = true;
//    seedToad(2, 2);
//    seedGlider(10, 10);
//    seedBeacon(50, 10);
//    seedOscillator(50, 30);
//    seedStillBlock(70, 40);
    seedRPentomino(50,30);
}

void Model::seedLifeRand()
{
    srand(time(0));
    int randomOffsetX = 1 + rand() % mapWidth - 7 - 1;
    int randomOffsetY = 1 + rand() % mapHeight - 3 - 1;
    generation1[3 + randomOffsetX][1 + randomOffsetY] = 1;
    generation1[3 + randomOffsetX][2 + randomOffsetY] = 1;
    generation1[3 + randomOffsetX][3 + randomOffsetY] = 1;
    generation1[3 + randomOffsetX][5 + randomOffsetY] = 1;
    generation1[3 + randomOffsetX][6 + randomOffsetY] = 1;
    generation1[3 + randomOffsetX][7 + randomOffsetY] = 1;
    generation1[2 + randomOffsetX][7 + randomOffsetY] = 1;
    generation1[1 + randomOffsetX][6 + randomOffsetY] = 1;
}

void Model::calculateNextGeneration()
{
    int neighbours = 0;
    for (int i = 0; i < mapHeight - 1; ++i) {
        for (int j = 0; j < mapWidth - 1; ++j) {
            //Computate next generation
            neighbours = countNeighbours(i, j);
            if (generation1[i][j] == 1) {
                if (neighbours < 2)
                    generation2[i][j] = 0;
                if (neighbours == 2 || neighbours == 3)
                    generation2[i][j] = 1;
                if (neighbours > 3)
                    generation2[i][j] = 0;
            } else if (neighbours == 3) {
                generation2[i][j] = 1;
            } else {
                generation2[i][j] = 0;
            }
        }
    }
    if(isSeeded)
        generationCount++;
    generation1.swap(generation2);
}

int Model::countNeighbours(int i, int j)
{
    int neighbours = 0;
    //N
    if (i != 0 && generation1[i - 1][j] == 1) neighbours++;
    //NE
    if (i != 0 && generation1[i - 1][j + 1] == 1) neighbours++;
    //E
    if (j != mapWidth - 1 && generation1[i][j + 1] == 1) neighbours++;
    //SE
    if (j != mapWidth - 1 && generation1[i + 1][j + 1] == 1) neighbours++;
    //S
    if (i != mapHeight - 1 && generation1[i + 1][j] == 1) neighbours++;
    //SW
    if (i != mapHeight - 1 && generation1[i + 1][j - 1] == 1) neighbours++;
    //W
    if (j != 0 && generation1[i][j - 1] == 1) neighbours++;
    //NW
    if (i != 0 && generation1[i - 1][j - 1] == 1) neighbours++;

    return neighbours;
}

void Model::reset()
{
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            generation1[i][j] = 0;
            generation2[i][j] = 0;
            generationCount = 0;
        }
    }
    isSeeded = false;
}

void Model::seedOscillator(int offsetX, int offsetY)
{
    //Oscillator
    generation1[1 + offsetY][0 + offsetX] = 1;
    generation1[1 + offsetY][1 + offsetX] = 1;
    generation1[1 + offsetY][2 + offsetX] = 1;
}

void Model::seedStillBlock(int offsetX, int offsetY)
{
    //Still block
    generation1[0 + offsetY][0 + offsetX] = 1;
    generation1[0 + offsetY][1 + offsetX] = 1;
    generation1[1 + offsetY][0 + offsetX] = 1;
    generation1[1 + offsetY][1 + offsetX] = 1;
}

void Model::seedGlider(int offsetX, int offsetY)
{
//Glider
    generation1[2 + offsetY][1 + offsetX] = 1;
    generation1[2 + offsetY][2 + offsetX] = 1;
    generation1[2 + offsetY][3 + offsetX] = 1;
    generation1[1 + offsetY][3 + offsetX] = 1;
    generation1[0 + offsetY][2 + offsetX] = 1;
}

void Model::seedBeacon(int offsetX, int offsetY)
{
    //Beacon
    generation1[0 + offsetY][0 + offsetX] = 1;
    generation1[0 + offsetY][1 + offsetX] = 1;
    generation1[1 + offsetY][0 + offsetX] = 1;
    generation1[1 + offsetY][1 + offsetX] = 1;
    generation1[2 + offsetY][2 + offsetX] = 1;
    generation1[2 + offsetY][3 + offsetX] = 1;
    generation1[3 + offsetY][2 + offsetX] = 1;
    generation1[3 + offsetY][3 + offsetX] = 1;
}

void Model::seedToad(int offsetX, int offsetY)
{
    //Toad
    generation1[0 + offsetY][1 + offsetX] = 1;
    generation1[0 + offsetY][2 + offsetX] = 1;
    generation1[0 + offsetY][3 + offsetX] = 1;
    generation1[1 + offsetY][0 + offsetX] = 1;
    generation1[1 + offsetY][1 + offsetX] = 1;
    generation1[1 + offsetY][2 + offsetX] = 1;
}

void Model::seedRPentomino(int offsetX, int offsetY)
{
    //R-Pentomino
    generation1[0 + offsetY][1 + offsetX] = 1;
    generation1[0 + offsetY][2 + offsetX] = 1;
    generation1[1 + offsetY][1 + offsetX] = 1;
    generation1[1 + offsetY][0 + offsetX] = 1;
    generation1[2 + offsetY][1 + offsetX] = 1;
}
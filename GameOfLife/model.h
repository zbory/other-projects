//
// Created by zbora on 2019-04-21.
//

#ifndef MULTIPLAYERTICTACTOE_MODEL_H
#define MULTIPLAYERTICTACTOE_MODEL_H

#include <vector>

const int MAP_WIDTH = 105;
const int MAP_HEIGHT = 65;


class Model {
public:
    Model();

    int getMapWidth();

    int getMapHeight();

    int getPosValue(int y, int x);

    int getGenerationCount();

    void reset();

    void seedLife();

    void seedLifeRand();

    void calculateNextGeneration();

    void seedOscillator(int offsetX, int offsetY);

    void seedStillBlock(int offsetX, int offsetY);

    void seedGlider(int offsetX, int offsetY);

    void seedBeacon(int offsetX, int offsetY);

    void seedToad(int offsetX, int offsetY);

    void seedRPentomino(int offsetX, int offsetY);

private:
    int mapWidth = MAP_WIDTH;
    int mapHeight = MAP_HEIGHT;
    std::vector<std::vector<int>> generation1;
    std::vector<std::vector<int>> generation2;

    int countNeighbours(int i, int j);
    bool isSeeded;
    int generationCount;
};


#endif //MULTIPLAYERTICTACTOE_MODEL_H

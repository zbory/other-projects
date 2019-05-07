#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include <cmath>
#include "colorLookupTable.h"

//Screen dimension constants
const int SCREEN_WIDTH = 650;
const int SCREEN_HEIGHT = 650;
const int bufferSize = 650;
int impulseSize = 50000;

void rippleWater(ColorLookupTable &colorTable);

void resetBuffers();

bool init();

void close();

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Texture *framebuffer;

int buffer1[bufferSize][bufferSize];
int buffer2[bufferSize][bufferSize];
uint32_t colorbuffer[bufferSize][bufferSize];
float damping = 0.95;


int main(int argc, char *args[])
{
    //Start up SDL and create window
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
        close();
        return -1;
    }

    srand(time(0));

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    bool rain = false;
    bool twoTone = false;
    bool isBlue = false;
    ColorLookupTable colorTable;
    int startTicks = SDL_GetTicks();

    resetBuffers();

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                buffer1[e.button.y][e.button.x] = impulseSize * 2;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    rain = !rain;
                }
                if (e.key.keysym.sym == SDLK_r) {
                    resetBuffers();
                }
                if (e.key.keysym.sym == SDLK_t) {
                    twoTone = true;
                }
            }
        }

        //Clear screen
        SDL_RenderClear(gRenderer);


        if (rain && SDL_GetTicks() - startTicks > 300) {
            buffer1[1 + rand() % (bufferSize - 1)][1 + rand() % (bufferSize - 1)] = rand() % impulseSize;
            startTicks = SDL_GetTicks();
        }
        rippleWater(colorTable);


        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    //Free resources and close SDL
    close();

    return 0;
}

void rippleWater(ColorLookupTable &colorTable)
{
    for (int i = 1; i < bufferSize - 1; ++i) {
        for (int j = 1; j < bufferSize - 1; ++j) {
            //Waveform
            buffer2[i][j] = (buffer1[i - 1][j] + buffer1[i + 1][j] +
                             buffer1[i][j + 1] + buffer1[i][j - 1]) / 2 - buffer2[i][j];

            buffer2[i][j] = buffer2[i][j] * damping;

            //Color
            if (buffer2[i][j] > 0) {

                float index = colorTable.getTableSize() / (1.0f * buffer2[i][j]) - 1;

//                SDL_Log(std::to_string(colorTable.getTableSize()).c_str());
//                SDL_Log(std::to_string(index).c_str());

                colorbuffer[i][j] = colorTable.getColorValue(index);
            } else
                colorbuffer[i][j] = 0;
        }
    }

    SDL_UpdateTexture(framebuffer, NULL, colorbuffer, bufferSize * sizeof(uint32_t));
    SDL_RenderCopy(gRenderer, framebuffer, NULL, NULL);
    SDL_Delay(16);

    int temp[bufferSize][bufferSize];
    std::copy(&buffer1[0][0], &buffer1[0][0] + bufferSize * bufferSize, &temp[0][0]);
    std::copy(&buffer2[0][0], &buffer2[0][0] + bufferSize * bufferSize, &buffer1[0][0]);
    std::copy(&temp[0][0], &temp[0][0] + bufferSize * bufferSize, &buffer2[0][0]);
}

void resetBuffers()
{
    for (int i = 0; i < bufferSize; ++i) {
        for (int j = 0; j < bufferSize; ++j) {
            buffer1[i][j] = 0;
            buffer2[i][j] = 0;
        }
    }
}

bool init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("RainbowWaves", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
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

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(gRenderer, &info);
//    for (int i = 0; i < 16; ++i) {
//        SDL_Log(SDL_GetPixelFormatName(info.texture_formats[i]));
//    }


    framebuffer = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                                    SCREEN_HEIGHT);

    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_ADD);

//    SDL_SetTextureColorMod(framebuffer, 196, 254, 255);

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void close()
{
    //Destroy window
    SDL_DestroyTexture(framebuffer);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();
}
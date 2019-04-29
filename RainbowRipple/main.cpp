#include <iostream>
#include <SDL.h>
#include <vector>
#include <tuple>


//Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int bufferSize = 600;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = nullptr;

//The window renderer
SDL_Renderer *gRenderer = nullptr;

//Buffer
SDL_Texture *framebuffer;

int buffer1[bufferSize][bufferSize];
int buffer2[bufferSize][bufferSize];
float damping = 0.97;

void rippleWater()
{
    for (int i = 1; i < bufferSize - 1; ++i) {
        for (int j = 1; j < bufferSize - 1; ++j) {
            buffer2[i][j] = (buffer1[i - 1][j] + buffer1[i + 1][j] +
                             buffer1[i][j + 1] + buffer1[i][j - 1]) / 2 - buffer2[i][j];

            buffer2[i][j] = buffer2[i][j] * damping;
        }
    }
//    drawPixels();
    SDL_UpdateTexture(framebuffer, NULL, buffer2, bufferSize * sizeof(int));
    SDL_RenderCopy(gRenderer, framebuffer, NULL, NULL);
    SDL_Delay(10);

    int temp[bufferSize][bufferSize];
    std::copy(&buffer1[0][0], &buffer1[0][0] + bufferSize * bufferSize, &temp[0][0]);
    std::copy(&buffer2[0][0], &buffer2[0][0] + bufferSize * bufferSize, &buffer1[0][0]);
    std::copy(&temp[0][0], &temp[0][0] + bufferSize * bufferSize, &buffer2[0][0]);
}

bool init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("RainboWaves", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
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

    framebuffer = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH,
                                    SCREEN_HEIGHT);

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();
}

int main(int argc, char *args[])
{
    //Start up SDL and create window
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
        close();
        return -1;
    }

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    for (int i = 1; i < bufferSize; ++i) {
        for (int j = 1; j < bufferSize; ++j) {
            buffer1[i][j] = 0;
            buffer2[i][j] = 0;
        }
    }

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                buffer1[e.button.y][e.button.x] = 50000;
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        rippleWater();


        //Update screen
        SDL_RenderPresent(gRenderer);
    }

    //Free resources and close SDL
    close();

    return 0;
}
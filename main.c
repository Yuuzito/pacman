#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const int width = 800;
static const int height = 800;
static const float xInicial = 35;
static const float yInicial = 35;

int main(int argc, char **argv)
{
    int MAPA[31][28] =
{
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -2, -1},
    {-1,  1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1,  1, -1},
    {-1,  1, -1,  0,  0, -1,  1, -1,  0,  0,  0, -1,  1, -1, -1,  1, -1,  0,  0,  0, -1,  1, -1,  0,  0, -1,  1, -1},
    {-1,  1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1,  1, -1},
    {-1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
    {-1,  1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1,  1, -1},
    {-1,  1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1,  1, -1},
    {-1,  1,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1,  1, -1},
    {-1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1,  0, -1, -1,  0, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1, -1},
    { 0,  0,  0,  0,  0, -1,  1, -1, -1, -1, -1, -1,  0, -1, -1,  0, -1, -1, -1, -1, -1,  1, -1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0, -1,  1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1,  1, -1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0, -1,  1, -1, -1,  0, -1, -1, -1,  0,  0, -1, -1, -1,  0, -1, -1,  1, -1,  0,  0,  0,  0,  0},
    {-1, -1, -1, -1, -1, -1,  1, -1, -1,  0, -1,  2,  3,  4,  5,  0,  0, -1,  0, -1, -1,  1, -1, -1, -1, -1, -1, -1},
    { 0,  0,  0,  0,  0,  0,  1,  0,  0,  0, -1,  0,  0,  0,  0,  0,  0, -1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0},
    {-1, -1, -1, -1, -1, -1,  1, -1, -1,  0, -1,  0,  0,  0,  0,  0,  0, -1,  0, -1, -1,  1, -1, -1, -1, -1, -1, -1},
    { 0,  0,  0,  0,  0, -1,  1, -1, -1,  0, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1,  1, -1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0, -1,  1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1, -1,  1, -1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0, -1,  1, -1, -1,  0, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1,  1, -1,  0,  0,  0,  0,  0},
    {-1, -1, -1, -1, -1, -1,  1, -1, -1,  0, -1, -1, -1, -1, -1, -1, -1, -1,  0, -1, -1,  1, -1, -1, -1, -1, -1, -1},
    {-1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
    {-1,  1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1,  1, -1},
    {-1,  1, -1, -1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1,  1, -1, -1, -1, -1,  1, -1},
    {-1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1,  1,  1,-10,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1, -1},
    {-1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1, -1},
    {-1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1,  1, -1, -1, -1},
    {-1, -2,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1, -2, -1},
    {-1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1},
    {-1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1},
    {-1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Pac-Man",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *pelota = IMG_Load("pelota.png");
    SDL_Surface *mapa = IMG_Load("mapa.jpg");
    SDL_Surface *fantasmaR = IMG_Load("fantasmaR.png");
    SDL_Surface *fantasmaRo = IMG_Load("fantasmaRo.png");
    SDL_Surface *fantasmaN = IMG_Load("FantasmaN.png");
    SDL_Surface *fantasmaC = IMG_Load("FantasmaC.png");
    SDL_Surface *pacman = IMG_Load("pacman.png");

    SDL_Texture *mapa_texture = SDL_CreateTextureFromSurface(renderer, mapa);
    SDL_Texture *pelota_texture = SDL_CreateTextureFromSurface(renderer, pelota);
    SDL_Texture *fantasmaR_texture = SDL_CreateTextureFromSurface(renderer, fantasmaR);
    SDL_Texture *fantasmaRo_texture = SDL_CreateTextureFromSurface(renderer, fantasmaRo);
    SDL_Texture *fantasmaN_texture = SDL_CreateTextureFromSurface(renderer, fantasmaN);
    SDL_Texture *fantasmaC_texture = SDL_CreateTextureFromSurface(renderer, fantasmaC);
    SDL_Texture *pacman_texture = SDL_CreateTextureFromSurface(renderer, pacman);

    SDL_FreeSurface(mapa);
    SDL_FreeSurface(pelota);
    SDL_FreeSurface(fantasmaR);
    SDL_FreeSurface(fantasmaRo);
    SDL_FreeSurface(fantasmaN);
    SDL_FreeSurface(fantasmaC);
    SDL_FreeSurface(pacman);

    SDL_Rect mapa_destination;
    SDL_Rect pelota_destination;
    SDL_Rect fantasmaR_destination;
    SDL_Rect fantasmaRo_destination;
    SDL_Rect fantasmaN_destination;
    SDL_Rect fantasmaC_destination;
    SDL_Rect pacman_destination;

    mapa_destination.x = 0;
    mapa_destination.y = 0;
    mapa_destination.w = width;
    mapa_destination.h = height;

    pelota_destination.x = xInicial;
    pelota_destination.y = yInicial;
    pelota_destination.w = 8;
    pelota_destination.h = 8;

    fantasmaR_destination.w = 30;
    fantasmaR_destination.h = 30;

    fantasmaRo_destination.w = 30;
    fantasmaRo_destination.h = 30;
    
    fantasmaN_destination.w = 30;
    fantasmaN_destination.h = 30;
    
    fantasmaC_destination.w = 30;
    fantasmaC_destination.h = 30;

    pacman_destination.w = 35;
    pacman_destination.h = 35;
    
    bool jugando = true;
    SDL_Event event;
    while(jugando)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                jugando = false;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, mapa_texture, NULL, &mapa_destination);

        for(int i=0;i<31;i++)
        {
            for(int j=0;j<28;j++)
            {
                if(MAPA[i][j]==1)
                {
                    pelota_destination.x = xInicial + (j-1)*28.8;
                    pelota_destination.y = yInicial + (i-1)*26;
                    SDL_RenderCopy(renderer, pelota_texture, NULL, &pelota_destination);
                }
                else if(MAPA[i][j]==2)
                {
                    fantasmaR_destination.x = xInicial + (j-1)*28.8;
                    fantasmaR_destination.y = yInicial + (i-1)*26;
                    SDL_RenderCopy(renderer, fantasmaR_texture, NULL, &fantasmaR_destination);
                }
                else if(MAPA[i][j]==3)
                {
                    fantasmaRo_destination.x = xInicial + (j-1)*28.8;
                    fantasmaRo_destination.y = yInicial + (i-1)*26;
                    SDL_RenderCopy(renderer, fantasmaRo_texture, NULL, &fantasmaRo_destination);
                }
                else if(MAPA[i][j]==4)
                {
                    fantasmaN_destination.x = xInicial + (j-1)*28.8;
                    fantasmaN_destination.y = yInicial + (i-1)*26;
                    SDL_RenderCopy(renderer, fantasmaN_texture, NULL, &fantasmaN_destination);
                }
                else if(MAPA[i][j]==5)
                {
                    fantasmaC_destination.x = xInicial + (j-1)*28.8;
                    fantasmaC_destination.y = yInicial + (i-1)*26;
                    SDL_RenderCopy(renderer, fantasmaC_texture, NULL, &fantasmaC_destination);
                }
                else if(MAPA[i][j]==-10)
                {
                    pacman_destination.x = xInicial + (j-1)*27.7;
                    pacman_destination.y = yInicial + (i-1)*25.4;
                    SDL_RenderCopy(renderer, pacman_texture, NULL, &pacman_destination);
                }
                else if(MAPA[i][j]==-2)
                {
                    pelota_destination.x = 27.7 + (j-1)*28.7;
                    pelota_destination.y = 25.4 + (i-1)*26;
                    pelota_destination.h = 25;
                    pelota_destination.w = 25;
                    SDL_RenderCopy(renderer, pelota_texture, NULL, &pelota_destination);
                    pelota_destination.h = 8;
                    pelota_destination.w = 8;
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(mapa_texture);
    SDL_DestroyTexture(pelota_texture);
    SDL_DestroyTexture(fantasmaR_texture);
    SDL_DestroyTexture(fantasmaRo_texture);
    SDL_DestroyTexture(fantasmaN_texture);
    SDL_DestroyTexture(fantasmaC_texture);
    SDL_DestroyTexture(pacman_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MatrizOG.h"
#include "posandmov.h"
#include "timeandinput.h"

static const int width = 800;
static const int height = 800;
static const float xInicial = 35;
static const float yInicial = 35;
int ancho = 0, altura = 1, scatter = 0, powerup,angulo=0;

int main(int argc, char *argv[])
{
    float cont_2=0,cont=0;
    int jugando=1;
    printf("Ingresar el nombre del archivo .txt a leer (.txt incluido) (Asegurar que se encuentre en la carpeta Laberintos): ");
	char Arch[96] = "Laberintos\\";
	char test = getchar();
	int ii = 0;
	while (test != '\n') {
		Arch[ii + 11] = test;
		ii++;
		test = getchar();
	}
	int pos[10];
	int** MAPA = crearLaberinto(&ancho, &altura, Arch, pos);
	ancho--;
	printf("\n %d %d %d\n ", MAPA[1][1], ancho, altura);
	int** Inter = crearIntersecciones(MAPA,altura,ancho);
	int mov[5] = { 0,0,0,0,0 };
	int tar[10];
	int dir[5] = { 2,2,2,2,2 };

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError()); return 0;
	}

    SDL_Window* window = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError()); return 0;
	}
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window); SDL_Quit(); return 0;
	}

    const Uint8* tecla = SDL_GetKeyboardState(NULL);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *pelota = IMG_Load("pelota.png");
    SDL_Surface *mapa = IMG_Load("mapa.jpg");
    SDL_Surface *fantasmaR = IMG_Load("fantasmaR.png");
    SDL_Surface *fantasmaRo = IMG_Load("fantasmaRo.png");
    SDL_Surface *fantasmaN = IMG_Load("FantasmaN.png");
    SDL_Surface *fantasmaC = IMG_Load("FantasmaC.png");
    SDL_Surface *pacman = IMG_Load("pacman.png");
    SDL_Surface *pacman_0 = IMG_Load("pacman_0.png");
    SDL_Surface *pacman_2 = IMG_Load("pacman_2.png");

    SDL_Texture *mapa_texture = SDL_CreateTextureFromSurface(renderer, mapa);
    SDL_Texture *pelota_texture = SDL_CreateTextureFromSurface(renderer, pelota);
    SDL_Texture *fantasmaR_texture = SDL_CreateTextureFromSurface(renderer, fantasmaR);
    SDL_Texture *fantasmaRo_texture = SDL_CreateTextureFromSurface(renderer, fantasmaRo);
    SDL_Texture *fantasmaN_texture = SDL_CreateTextureFromSurface(renderer, fantasmaN);
    SDL_Texture *fantasmaC_texture = SDL_CreateTextureFromSurface(renderer, fantasmaC);
    SDL_Texture *pacman_texture = SDL_CreateTextureFromSurface(renderer, pacman);
    SDL_Texture *pacman_0_texture = SDL_CreateTextureFromSurface(renderer, pacman_0);
    SDL_Texture *pacman_2_texture = SDL_CreateTextureFromSurface(renderer, pacman_2);

    SDL_FreeSurface(mapa);
    SDL_FreeSurface(pelota);
    SDL_FreeSurface(fantasmaR);
    SDL_FreeSurface(fantasmaRo);
    SDL_FreeSurface(fantasmaN);
    SDL_FreeSurface(fantasmaC);
    SDL_FreeSurface(pacman);
    SDL_FreeSurface(pacman_0);
    SDL_FreeSurface(pacman_2);

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

    fantasmaR_destination.w = 39;
    fantasmaR_destination.h = 39;

    fantasmaRo_destination.w = 39;
    fantasmaRo_destination.h = 39;
    
    fantasmaN_destination.w = 39;
    fantasmaN_destination.h = 39;
    
    fantasmaC_destination.w = 39;
    fantasmaC_destination.h = 39;

    pacman_destination.w = 37;
    pacman_destination.h = 37;

    SDL_Event event;

    int inputdec(event,tecla,MAPA,Inter,pos,tar,mov,dir);

    while(jugando)
    {
        if(cont_2>60)
        {
            cont_2=0;
        }
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                jugando = 0;
            }
            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    angulo = 0;
                    break;
                case SDLK_LEFT:
                    angulo = 180;
                    break;
                case SDLK_DOWN:
                    angulo = 90;
                    break;
                case SDLK_UP:
                    angulo = 270;
                    break;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, mapa_texture, NULL, &mapa_destination);

        for(int i=0;i<31;i++)
        {
            for(int j=0;j<28;j++)
            {
                if(cont>60)
                {
                    cont=0;
                }
                if(MAPA[i][j]==1)
                {
                    pelota_destination.x = xInicial + (j-1)*28.8;
                    pelota_destination.y = yInicial + (i-1)*26;
                    SDL_RenderCopy(renderer, pelota_texture, NULL, &pelota_destination);
                }
                else if(MAPA[i][j]==2)
                {
                    fantasmaR_destination.x = 22 + (j-1)*28.7;
                    fantasmaR_destination.y = 24 + (i-1)*25.7;
                    SDL_RenderCopy(renderer, fantasmaR_texture, NULL, &fantasmaR_destination);
                }
                else if(MAPA[i][j]==3)
                {
                    fantasmaRo_destination.x = 22 + (j-1)*28.7;
                    fantasmaRo_destination.y = 24 + (i-1)*25.7;
                    SDL_RenderCopy(renderer, fantasmaRo_texture, NULL, &fantasmaRo_destination);
                }
                else if(MAPA[i][j]==4)
                {
                    fantasmaN_destination.x = 22 + (j-1)*28.7;
                    fantasmaN_destination.y = 24 + (i-1)*25.7;
                    SDL_RenderCopy(renderer, fantasmaN_texture, NULL, &fantasmaN_destination);
                }
                else if(MAPA[i][j]==5)
                {
                    fantasmaC_destination.x = 22 + (j-1)*28.7;
                    fantasmaC_destination.y = 24 + (i-1)*25.7;
                    SDL_RenderCopy(renderer, fantasmaC_texture, NULL, &fantasmaC_destination);
                }
                else if(MAPA[i][j]==-10)
                {
                    pacman_destination.x = 22 + (j-1)*28.75;
                    pacman_destination.y = 22 + (i-1)*25.9;
                    if(cont<=15)
                    {
                        SDL_RenderCopyEx(renderer, pacman_0_texture, NULL, &pacman_destination, angulo, NULL, SDL_FLIP_NONE);
                    }
                    else if(cont<=30)
                    {
                        SDL_RenderCopyEx(renderer, pacman_texture, NULL, &pacman_destination, angulo, NULL, SDL_FLIP_NONE);
                    }
                    else if(cont<=45)
                    {
                        SDL_RenderCopyEx(renderer, pacman_2_texture, NULL, &pacman_destination, angulo, NULL, SDL_FLIP_NONE);
                    }
                    else
                    {
                        SDL_RenderCopyEx(renderer, pacman_texture, NULL, &pacman_destination, angulo, NULL, SDL_FLIP_NONE);
                    }
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
                cont+=0.010;
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(32);
        cont_2+=1;
        if(cont_2==30)
        {
            MAPA[23][13]=0;
            MAPA[23][14]=-10;
        }
        else if(cont_2==60)
        {
            MAPA[23][14]=0;
            MAPA[23][15]=-10;
        }
    }
    SDL_DestroyTexture(mapa_texture);
    SDL_DestroyTexture(pelota_texture);
    SDL_DestroyTexture(fantasmaR_texture);
    SDL_DestroyTexture(fantasmaRo_texture);
    SDL_DestroyTexture(fantasmaN_texture);
    SDL_DestroyTexture(fantasmaC_texture);
    SDL_DestroyTexture(pacman_texture);
    SDL_DestroyTexture(pacman_0_texture);
    SDL_DestroyTexture(pacman_2_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
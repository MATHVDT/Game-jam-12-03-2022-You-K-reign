#ifndef DESSIN_HPP
#define DESSIN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

void dessiner(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst);
void dessinerIles(SDL_Renderer *renderer, SDL_Texture *texture, double angle[9]);
void dessinerEtat(SDL_Renderer *renderer, SDL_Texture *textures[], int etats[9]);
void dessinerRessource(SDL_Renderer *renderer, SDL_Texture *textures[], int ressources[9]);

#endif
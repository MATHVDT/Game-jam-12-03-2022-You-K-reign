#ifndef DESSIN_HPP
#define DESSIN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

void dessiner(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst);
void dessinerIle(SDL_Renderer *renderer, SDL_Texture *texture, double angle[9], int id_pays);
void dessinerEtat(SDL_Renderer *renderer, SDL_Texture *texturesEtat[], int etat, int id_pays);
void dessinerRessource(SDL_Renderer *renderer, SDL_Texture *texturesRessourcesBases[], int ressource, int id_pays);
void dessinerBouton(SDL_Renderer *renderer, SDL_Texture *texturesBouton[], bool etatBouton, int idBouton);

#endif
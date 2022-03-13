#include "dessin.hpp"

void dessiner(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void dessinerIle(SDL_Renderer *renderer, SDL_Texture *texture, double angle[9], int idPays)
{
    SDL_Rect src{0, 0, 0, 0};
    SDL_Rect dst{0, 0, 200, 200};

    dst.x = 0 + idPays%3  * 200;
    dst.y = 0 + idPays/3  * 200;
    SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
    SDL_Point center = {dst.w / 2, dst.h / 2};
    SDL_RendererFlip flip = static_cast<SDL_RendererFlip>(SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, texture, &src, &dst, angle[idPays], &center, flip);
}

void dessinerEtat(SDL_Renderer *renderer, SDL_Texture *texturesEtat[], int etat, int idPays)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};

    dst.x = 50 + idPays%3 * 200;
    dst.y = 50 + idPays/3 * 200;
    SDL_QueryTexture(texturesEtat[etat-1], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesEtat[etat-1], &src, &dst);
}

void dessinerRessource(SDL_Renderer *renderer, SDL_Texture *texturesRessourcesBases[], int ressource, int idPays)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};
    dst.x = 100 + idPays%3 * 200;
    dst.y = 100 + idPays/3 * 200;
    SDL_QueryTexture(texturesRessourcesBases[ressource], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessourcesBases[ressource], &src, &dst);
}

void dessinerBouton(SDL_Renderer *renderer, SDL_Texture *texturesBouton[], bool etatBouton, int idBouton)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,320,90};

    dst.x = 630;
    dst.y = 5 + idBouton * 100;
    SDL_QueryTexture(texturesBouton[idBouton + etatBouton], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesBouton[idBouton + etatBouton], &src, &dst);
}
#include "dessin.hpp"

void dessiner(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void dessinerIle(SDL_Renderer *renderer, SDL_Texture *texture, double angle[9], int id_pays)
{
    SDL_Rect src{0, 0, 0, 0};
    SDL_Rect dst{0, 0, 200, 200};

    dst.x = 0 + id_pays%3  * 200;
    dst.y = 0 + id_pays/3  * 200;
    SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
    SDL_Point center = {dst.w / 2, dst.h / 2};
    SDL_RendererFlip flip = static_cast<SDL_RendererFlip>(SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, texture, &src, &dst, angle[id_pays], &center, flip);
}

void dessinerEtat(SDL_Renderer *renderer, SDL_Texture *texturesEtat[], int etat, int id_pays)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};

    dst.x = 50 + id_pays%3 * 200;
    dst.y = 50 + id_pays/3 * 200;
    SDL_QueryTexture(texturesEtat[etat-1], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesEtat[etat-1], &src, &dst);
}

void dessinerRessource(SDL_Renderer *renderer, SDL_Texture *texturesRessourcesBases[], int ressource, int id_pays, int ressourcedispo)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};
    dst.x = 112.5 + id_pays%3 * 200;
    dst.y = 112.5 + id_pays/3 * 200;
    SDL_QueryTexture(texturesRessourcesBases[ressource], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessourcesBases[ressource], &src, &dst);

    SDL_Rect src2{0,0,0,0};
    SDL_Rect dst2{0,0,30,30};
    dst2.x = 97.5 + id_pays%3 * 200;
    dst2.y = 122.5 + id_pays/3 * 200;
    SDL_QueryTexture(texturesRessourcesBases[9 + ressourcedispo], nullptr, nullptr, &src2.w, &src2.h);
    SDL_RenderCopy(renderer, texturesRessourcesBases[9 + ressourcedispo], &src2, &dst2);
}

void dessinerReligion(SDL_Renderer *renderer, SDL_Texture *textureTexte[], int religion, int id_pays)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};
    dst.x = 150 + id_pays%3 * 200;
    dst.y = 150 + id_pays/3 * 200;
    SDL_QueryTexture(textureTexte[religion/5], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, textureTexte[religion/5], &src, &dst);
}
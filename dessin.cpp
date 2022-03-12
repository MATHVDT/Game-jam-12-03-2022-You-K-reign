#include "dessin.hpp"

void dessiner(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void dessinerIles(SDL_Renderer *renderer, SDL_Texture *texture, double angle[9])
{
    SDL_Rect src{0, 0, 0, 0};
    SDL_Rect dst{0, 0, 200, 200};

    for (int i = 0; i < 3; i++)
    {
        dst.x = 0 + i * 200;
        for (int j = 0; j < 3; j++)
        {
            dst.y = 0 + j * 200;
            SDL_QueryTexture(texture, nullptr, nullptr, &src.w, &src.h);
            SDL_Point center = {dst.w / 2, dst.h / 2};
            SDL_RendererFlip flip = static_cast<SDL_RendererFlip>(SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, texture, &src, &dst, angle[0 + i + j], &center, flip);
        }
    }
}

void dessinerEtat(SDL_Renderer *renderer, SDL_Texture *textures[], int etats[9])
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};
    for (int i = 0; i < 3; i++)
    {
        dst.x = 50 + i * 200;
        for (int j = 0; j < 3; j++)
        {
            dst.y = 50 + j * 200;
            SDL_QueryTexture(textures[2 + etats[i+j]], nullptr, nullptr, &src.w, &src.h);
            SDL_RenderCopy(renderer, textures[2 + etats[i+j]], &src, &dst);
        }
    }
}

void dessinerRessource(SDL_Renderer *renderer, SDL_Texture *textures[], int ressources[9])
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,50,50};
    for (int i = 0; i < 3; i++)
    {
        dst.x = 100 + i * 200;
        for (int j = 0; j < 3; j++)
        {
            dst.y = 100 + j * 200;
            SDL_QueryTexture(textures[ressources[i * 3 + j]], nullptr, nullptr, &src.w, &src.h);
            SDL_RenderCopy(renderer, textures[ressources[i * 3 + j]], &src, &dst);
        }
    }
}
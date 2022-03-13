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

void dessinerBouton(SDL_Renderer *renderer, SDL_Texture *texturesBouton[], bool etatBouton, int idBouton)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,320,72};

    dst.x = 630;
    dst.y = 5 + idBouton * 77;
    SDL_QueryTexture(texturesBouton[2 * idBouton + etatBouton], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesBouton[2 * idBouton + etatBouton], &src, &dst);
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
    dst2.x = 90 + id_pays%3 * 200;
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

void dessinerRessourcePrimaire(SDL_Renderer *renderer, SDL_Texture *texturesRessources[], int ressource, int ressourceDispo, int ressourceMax)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,10,20};
    dst.x = 1035;
    dst.y = 55 + ressource * 42;
    SDL_QueryTexture(texturesRessources[ressourceDispo], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[ressourceDispo], &src, &dst);

    dst.x = 1055;
    SDL_QueryTexture(texturesRessources[6], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[6], &src, &dst);

    dst.x = 1075;
    SDL_QueryTexture(texturesRessources[ressourceMax], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[ressourceMax], &src, &dst);
}

void dessinerRessourceSecondaire(SDL_Renderer *renderer, SDL_Texture *texturesRessources[], int ressource, int ressourceDispo, int ressourceMax)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,10,20};
    dst.x = 1035;
    dst.y = 480 + ressource * 42;
    SDL_QueryTexture(texturesRessources[ressourceDispo], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[ressourceDispo], &src, &dst);

    dst.x = 1055;
    SDL_QueryTexture(texturesRessources[6], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[6], &src, &dst);

    dst.x = 1075;
    SDL_QueryTexture(texturesRessources[ressourceMax], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[ressourceMax], &src, &dst);
}

void dessinerPARestant(SDL_Renderer *renderer, SDL_Texture *texturesRessources[], int ptAction)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,320,108};
    dst.x = 630;
    dst.y = 465;
    SDL_QueryTexture(texturesRessources[8], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[8], &src, &dst);

    dst.w = 20;
    dst.h = 20;
    dst.y = 500;
    dst.x = 735;
    SDL_QueryTexture(texturesRessources[ptAction], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[ptAction], &src, &dst);

    dst.x = 755;
    SDL_QueryTexture(texturesRessources[6], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[6], &src, &dst);

    dst.x = 775;
    SDL_QueryTexture(texturesRessources[5], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[5], &src, &dst);
}

void dessinerToursRestants(SDL_Renderer *renderer, SDL_Texture *texturesRessources[], int nbTourEcoule)
{
    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,20,20};
    //dst.x = 635;
    dst.y = 530;
    /*SDL_QueryTexture(texturesRessources[7], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[7], &src, &dst);*/

    dst.x = 735;
    SDL_QueryTexture(texturesRessources[nbTourEcoule], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[nbTourEcoule], &src, &dst);

    dst.x = 755;
    SDL_QueryTexture(texturesRessources[6], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[6], &src, &dst);

    dst.x = 775;
    SDL_QueryTexture(texturesRessources[7], nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources[7], &src, &dst);
}

void dessinerNouveauTour(SDL_Renderer *renderer, SDL_Texture *texturesRessources, SDL_Texture *textureMenu)
{
    SDL_RenderClear(renderer);
    SDL_Rect srcFondMenu{0, 0, 0, 0};
    SDL_Rect dstFondMenu{0, 0, 1100, 600};

    SDL_QueryTexture(textureMenu, nullptr, nullptr, &srcFondMenu.w, &srcFondMenu.h);

    dessiner(renderer, textureMenu, srcFondMenu, dstFondMenu);

    SDL_Rect src{0,0,0,0};
    SDL_Rect dst{0,0,250,50};
    dst.x = 425;
    dst.y = 275;
    SDL_QueryTexture(texturesRessources, nullptr, nullptr, &src.w, &src.h);
    SDL_RenderCopy(renderer, texturesRessources, &src, &dst);
}
#include "Bouton.hpp"

SDL_Texture *Bouton::_textureBoutons[12];

Bouton::Bouton(int idBouton, bool etatBouton)
{
    _idBouton = idBouton;
    _etatBouton = etatBouton;
}


void Bouton::chargerTexture(SDL_Renderer * renderer)
{
    SDL_Surface *imagesBouton[12];

    imagesBouton[0] = IMG_Load("../img/bouton_accord_commercial_unselec.png");
    imagesBouton[1] = IMG_Load("../img/bouton_accord_commercial_selec.png");
    imagesBouton[2] = IMG_Load("../img/bouton_acheter_unselec.png");
    imagesBouton[3] = IMG_Load("../img/bouton_acheter_selec.png");
    imagesBouton[4] = IMG_Load("../img/bouton_convertir_unselec.png");
    imagesBouton[5] = IMG_Load("../img/bouton_convertir_selec.png");
    imagesBouton[6] = IMG_Load("../img/bouton_guerre_militaire_unselec.png");
    imagesBouton[7] = IMG_Load("../img/bouton_guerre_militaire_selec.png");
    imagesBouton[8] = IMG_Load("../img/bouton_guerre_religieuse_unselec.png");
    imagesBouton[9] = IMG_Load("../img/bouton_guerre_religieuse_selec.png");
    imagesBouton[10] = IMG_Load("../img/bouton_transformer_unselec.png");
    imagesBouton[11] = IMG_Load("../img/bouton_transformer_selec.png");

    for (int i = 0; i < 3; i++)
    {
        _textureBoutons[i] = SDL_CreateTextureFromSurface(renderer, imagesBouton[i]);
        SDL_FreeSurface(imagesBouton[i]);
    }
} 

void Bouton::chargerBouton(SDL_Texture * texturesBouton[])
{
    for (int i = 0; i < 2; i++)
    {
        _textureBoutonId[i] = texturesBouton[2*_idBouton+i];
    }

    _position.x = 630;
    _position.y = 5 + _idBouton * 100;;
    _position.w = 320;
    _position.h = 90;
}

bool Bouton::detectionClique(int xSouris, int ySouris)
{
    bool clique = false;

    if ((xSouris>_position.x) && (xSouris<_position.x+_position.w) && (ySouris>_position.y) && (ySouris<_position.y+_position.h))
    {
        clique = true;
    }

    return clique;
}


void Bouton::afficherBouton(SDL_Renderer * renderer)
{
    dessinerBouton(renderer,_textureBoutonId,_etatBouton,_idBouton);
}

void Bouton::detruireTextureBouton()
{
    for (int i = 0; i < 2; i++)
    {
        SDL_DestroyTexture(_textureBoutonId[i]);
    }
}

void Bouton::detruireTexture()
{
    for (int i = 0; i < 6; i++)
    {
        SDL_DestroyTexture(_textureBoutons[i]);
    }
}
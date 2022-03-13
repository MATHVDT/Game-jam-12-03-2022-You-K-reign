#ifndef __BOUTON_HPP__
#define __BOUTON_HPP__

#include "dessin.hpp"
#include <iostream>

using namespace std;

class Bouton
{
    private:
        int _idBouton;
        bool _etatBouton;
        SDL_Rect _position;

    public:
        static SDL_Texture *_textureBoutons[12];

    public:
        Bouton(int idBouton, bool etatBouton);
        ~Bouton();
        void static chargerTexture(SDL_Renderer *);

        bool detectionClique(int xSouris, int ySouris);
        void afficherBouton(SDL_Renderer *);

        bool getEtatBouton();
        void setEtatBouton(bool a);

        void static detruireTexture();
};

#endif
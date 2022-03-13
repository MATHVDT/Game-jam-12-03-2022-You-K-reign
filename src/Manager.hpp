#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include "dessin.hpp"
#include "Pays.hpp"
#include "Joueur.hpp"
#include "Bouton.hpp"

using namespace std;

class Manager
{
    private:
        Pays *_tabPays[9];
        Joueur _joueur;
        Bouton *_tabBouton[6];
        SDL_Texture *_textureFondMenu;
        SDL_Texture *_textureRessourcesMenu;
    
    private:
        void chargerTexture(SDL_Renderer *);
        void detruireTexture();
        void initPays();
        void initJoueur();
        void initBouton();

    public:
        void afficher();
        void initJeu();
};

#endif
#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include "dessin.hpp"
#include "Pays.hpp"
#include "Joueur.hpp"
#include "Menu.hpp"
#include "Bouton.hpp"

using namespace std;

class Manager
{
<<<<<<< HEAD
    private:
        Pays *_tabPays[9];
        Joueur _joueur;
        Bouton *_tabBouton[6];
        Menu _menu;
        SDL_Texture *_textureFondInterface;
        SDL_Texture *_textureRessourcesInterface;
    
    private:
        void chargerTexture(SDL_Renderer *);
        void detruireTexture();
        void initPays();
        void initJoueur(Pays *paysJoueur);
        void initBouton();

    public:
        Manager();
        ~Manager();  

        void afficher(SDL_Renderer *);
        void initJeu(SDL_Renderer *);
=======
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

    int ileChoisie(int xMouse, int yMouse);

public:
    void afficher();
    void initJeu();
>>>>>>> 4b250ff2904a3e213bb148415dc211b4651fbb8d
};

#endif
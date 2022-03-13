#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <list>

#include "dessin.hpp"
#include "Pays.hpp"
#include "Joueur.hpp"
#include "Menu.hpp"
#include "Bouton.hpp"

using namespace std;

class Manager
{
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

    void creerAlliance();

    int ileChoisie(int xMouse, int yMouse);

};

#endif
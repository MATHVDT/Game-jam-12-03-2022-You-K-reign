#ifndef __MANAGER_HPP__
#define __MANAGER_HPP__

#include <iostream>
#include <list>

#include "dessin.hpp"
#include "Pays.hpp"
#include "Joueur.hpp"
#include "Menu.hpp"
#include "Bouton.hpp"

#include "EnumBouton.hpp"

enum BOUTON
{
    btnAccord = 0,
    btnAcheter = 1,
    btnConvertir = 2,
    btnGuerreMilitaire = 3,
    btnGuerreReligueuse = 4,
    btnTransformer = 5
};

using namespace std;

class Manager
{
private:
    Pays *_tabPays[9];
    Joueur _joueur;
    Bouton *_tabBouton[6];
    Menu _menu;
    SDL_Texture *_textureMenuFond;
    SDL_Texture *_textureFondInterface;
    SDL_Texture *_textureRessourcesInterface;
    SDL_Texture *_textureNouveauTour;
    int _nbTourRestant;

private:
    void chargerTexture(SDL_Renderer *);
    void detruireTexture();
    void initPays();
    void initJoueur(Pays *paysJoueur);
    void initBouton();

    void checkBouton(int xMouse, int yMouse);
    void creerAlliance();

    int ileChoisie(int xMouse, int yMouse);
    void tour(int idIleChoisie, int &nbTourEcoule, SDL_Renderer *renderer);
    bool checkVictoire();

public:
    Manager();
    ~Manager();

    void afficher(SDL_Renderer *);
    void initJeu(SDL_Renderer *);
    void jeu(SDL_Renderer *renderer);
    bool Partie(int, SDL_Renderer *);
};

#endif
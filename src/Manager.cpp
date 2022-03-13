#include "Manager.hpp"

void Manager::chargerTexture(SDL_Renderer * renderer)
{
    Pays::chargerTexture(renderer);
    Bouton::chargerTexture(renderer);

    //Charger Texture Menu Ressource
    SDL_Surface *imageRessourceMenu;

    imageRessourceMenu = IMG_Load("../img/menu/interface_ressource_verticale.png");

    _textureRessourcesMenu = SDL_CreateTextureFromSurface(renderer, imageRessourceMenu);
    SDL_FreeSurface(imageRessourceMenu);

    //Charger Texture Fond Menu
    SDL_Surface *imageFondMenu;

    imageFondMenu = IMG_Load("../img/menu/fond_menu.png");

    _textureFondMenu = SDL_CreateTextureFromSurface(renderer, imageFondMenu);
    SDL_FreeSurface(imageFondMenu);
}

void Manager::detruireTexture()
{
    SDL_DestroyTexture(_textureFondMenu);
    SDL_DestroyTexture(_textureRessourcesMenu);
    Bouton::detruireTexture();
    Pays::detruireTexture();
}

void Manager::afficher()
{
    SDL_DestroyTexture(_textureFondMenu);
    SDL_DestroyTexture(_textureRessourcesMenu);
    Bouton::detruireTexture();
    Pays::detruireTexture();
}

void Manager::afficher()
{
    
} 

void Manager::initPays()
{
    _tabPays[0] = new Pays(0, "Ukraine", 10, RessourceBase::RB0, EtatPays::Neutre);
    _tabPays[1] = new Pays(1, "Russie", 15, RessourceBase::RB1, EtatPays::Neutre);
    _tabPays[2] = new Pays(2, "Serbie", 5, RessourceBase::RB2, EtatPays::Neutre);
    _tabPays[3] = new Pays(3, "Bosnie", 10, RessourceBase::RB3, EtatPays::Neutre);
    _tabPays[4] = new Pays(4, "Slovaquie", 100, RessourceBase::RB4, EtatPays::Neutre);
    _tabPays[5] = new Pays(5, "Pologne", 15, RessourceBase::RB5, EtatPays::Neutre);
    _tabPays[6] = new Pays(6, "Chypre", 20, RessourceBase::RB6, EtatPays::Neutre);
    _tabPays[7] = new Pays(7, "Malte", 5, RessourceBase::RB7, EtatPays::Neutre);
    _tabPays[8] = new Pays(8, "Corse", 0, RessourceBase::RB8, EtatPays::Neutre);
}

void Manager::initJoueur()
{
    _joueur = Joueur(_tabPays[4]);
}

void Manager::initBouton()
{
    _tabBouton[0] = new Bouton(0,false);
    _tabBouton[1] = new Bouton(1,false);
    _tabBouton[2] = new Bouton(2,false);
    _tabBouton[3] = new Bouton(3,false);
    _tabBouton[4] = new Bouton(4,false);
    _tabBouton[5] = new Bouton(5,false);
}
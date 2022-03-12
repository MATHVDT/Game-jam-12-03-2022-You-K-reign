#ifndef __PAYS_HPP__
#define __PAYS_HPP__

#include <iostream>

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Ressource.hpp"
#include "EtatPays.hpp"

using namespace std;

class Pays
{
private:
    int _idPays;
    string _nomPays;
    int _religion; // de 0 => 10
    RessourceBase _ressource;

    EtatPays _etat;
    int _compteurEtat;
    int _maxProductionRessource;
    int _ressourceDispo;
    vector<Pays *> _alliance;

private:
    static int _tempsAccord;
    static int _tempsGuerre;

    static double _angle[9];
    static SDL_Texture *_textureIle;
    static SDL_Texture *_textureEtat[3];
    static SDL_Texture *_textureRessourcesBase[9];
    static SDL_Texture *_textureRessourcesCraft[3];

public:
    Pays(int idPays, string nom,
         int religion,
         RessourceBase ressource,
         EtatPays etat = EtatPays::Neutre);

    ~Pays() = default;

    void afficherConsole();
    void afficherPays(SDL_Renderer *);

    // Getter
    int getId() { return _idPays; }
    string getNom() { return _nomPays; }
    RessourceBase getRessource() { return _ressource; }
    int getMaxProduction() { return _maxProductionRessource; }
    int getRessourceDispo() { return _ressourceDispo; }
    vector<Pays *> getAlliance() { return _alliance; }

    // Action
    void nouveauTour();
    void annexer();
    bool accordCommercial();
    RessourceBase vendreRessource(int & ptActionJoueur);
    void convertir(int tauxConversion);
    void chargerTexture(SDL_Renderer *);


private:
    void actualiserEtat();
    void guerreDeclaree(Pays &pays);
};

#endif
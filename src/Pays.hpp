#ifndef __PAYS_HPP__
#define __PAYS_HPP__

#include <iostream>

#include <vector>

#include "Ressource.hpp"
#include "EtatPays.hpp"
#include "dessin.hpp"

using namespace std;

class Pays
{
private:
    int _idPays;
    string _nomPays;
    int _religion; // de 0 => 100
    RessourceBase _ressource;

    EtatPays _etat;
    int _compteurEtat;
    int _maxProductionRessource;
    int _ressourceDispo;
    vector<Pays *> _alliance;

private:
    static int _tempsAccord;
    static int _tempsGuerre;

public:
    static double _angle[9];
    static SDL_Texture *_textureIle;
    static SDL_Texture *_textureEtat[3];
    static SDL_Texture *_textureRessourcesBase[15];
    static SDL_Texture *_textureRessourcesCraft[3];
    static SDL_Texture *_textureText[21];

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
    int getCompteur() { return _compteurEtat; }
    int getPopFidele() { return _religion; }
    RessourceBase getRessource() { return _ressource; }
    int getMaxProduction() { return _maxProductionRessource; }
    int getRessourceDispo() { return _ressourceDispo; }
    vector<Pays *> getAlliance() { return _alliance; }

    // Setter
    void setAlliance(const vector<Pays *> alliance) { _alliance = alliance; };

    // Action
    void nouveauTour();
    void annexer();
    bool accordCommercial();
    RessourceBase vendreRessource(int &ptActionJoueur);
    bool convertir(int tauxConversion);

public:
    void static chargerTexture(SDL_Renderer *);
    void static detruireTexture();

private:
    void actualiserEtat();
    void guerreDeclaree(Pays &pays);
};

#endif
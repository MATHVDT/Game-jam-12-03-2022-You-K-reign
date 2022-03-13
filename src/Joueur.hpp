#ifndef __JOUEUR_HPP__
#define __JOUEUR_HPP__

#include <iostream>
#include <vector>

using namespace std;

#include "Pays.hpp"
#include "Ressource.hpp"
// class Pays;

class Joueur
{
private:
    Pays *_pays;
    int _ptAction;

    vector<Pays *> _paysAnnexes;

    int _stockRB[9];
    int _stockRC[3];

private:
    static const int _stockRBMax;
    static const int _stockRCMax;

    static const int _coupAttaqueArmee;
    static const int _coupAttaqueReligion;
    static const int _coupAccordCommercial;
    static const int _coupConvertir;
    static const int _coupTransformer;

public:
    static SDL_Texture *_textureRessources[7];

public:
    Joueur(Pays *paysJoueur);
    ~Joueur();

    void afficherJoueur(SDL_Renderer *renderer);

    // Getter
    Pays *getPays() { return _pays; }
    int getPtAction() { return _ptAction; }

    int *getStockRB() { return _stockRB; }
    int *getStockRC() { return _stockRC; }

    int getStockRBi(int i);
    int getStockRCi(int i);

    // Getter static
    int getStockRBMax() { return _stockRBMax; }
    int getStockRCMax() { return _stockRCMax; }

    // Action
    void donnerPointAction(int pt = 5);
    string accordCommercial(Pays &pays);
    string convertir(Pays &pays);

    // Attaque
    string attaqueArmee(Pays &pays);
    string attaqueReligion(Pays &pays);

    // Ressources
    void static chargerTexture(SDL_Renderer *renderer);
    void static detruireTexture();
};

#endif
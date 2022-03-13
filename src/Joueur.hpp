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
    int _ptAction;

    vector<Pays *> _paysPossedes;

    int _stockRB[9];
    int _stockRC[3];

private:
    static const int _stockRBMax;
    static const int _stockRCMax;

    static const int _coupAttaqueArmee;
    static const int _coupAttaqueReligion;
    static const int _coupAccordCommercial;
    static const int _coupAcheterRessource;
    static const int _coupAcheterRessourceAccord;
    static const int _coupConvertir;
    static const int _coupTransformer;

public:
    static SDL_Texture *_textureRessources[8];

public:
    Joueur();
    ~Joueur();

    void initJoueur(Pays *paysJoueur);

    void afficherJoueur(SDL_Renderer *renderer, int nbTourRestant);

    // Getter
    Pays *getPaysOrigin();
    int getNbPaysPossedes() { return _paysPossedes.size(); }
    int getPtAction() { return _ptAction; }

    int *getStockRB() { return _stockRB; }
    int *getStockRC() { return _stockRC; }

    int getStockRBi(int i);
    int getStockRCi(int i);

    // Setter tmp un peu bizzare parce que c'est des +
    void setStockRBi(int i, int qte) { _stockRB[i] = (_stockRB[i] + qte <= _stockRBMax ? qte : _stockRBMax); }
    void setStockRCi(int i, int qte) { _stockRC[i] = (_stockRC[i] + qte <= _stockRCMax ? qte : _stockRCMax); }

    // Getter static
    static int getStockRBMax() { return _stockRBMax; }
    static int getStockRCMax() { return _stockRCMax; }

    // Action
    void nouveauTour();
    void donnerPointAction(int pt = 5);
    string transformerRessource(); // test ok
    string accordCommercial(Pays &pays);
    string convertir(Pays &pays); // test ok
    string acheter(Pays &pays);   // test ok2

    // Attaque
    string attaqueArmee(Pays &pays);
    string attaqueReligion(Pays &pays);

    //Ressources
    void static chargerTexture(SDL_Renderer *renderer);
    void static detruireTexture();

private:
    void annexerPays(Pays &pays); // test ok
    string acheterRessourcePaysNeutre(Pays &pays);
    string acheterRessourcePaysAccord(Pays &pays);
    bool checkAssezPtAction(int coup, string &message);
    bool checkAssezRessource(int pourcentage, string &message);
};

#endif
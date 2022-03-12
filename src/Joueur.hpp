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
    Joueur(Pays *paysJoueur);
    ~Joueur();

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
    void nouveauTour();
    void donnerPointAction(int pt = 5);
    string accordCommercial(Pays &pays);
    string convertir(Pays &pays);
    string acheter(Pays & pays);

    // Attaque
    string attaqueArmee(Pays &pays);
    string attaqueReligion(Pays &pays);

private:
    void annexerPays(Pays &pays);
    string acheterRessourcePaysNeutre(Pays &pays);
    string acheterRessourcePaysAccord(Pays &pays);
};

#endif
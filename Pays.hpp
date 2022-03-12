#ifndef __PAYS_HPP__
#define __PAYS_HPP__

#include <iostream>
#include <vector>

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

    // Texture SDL2 _texture

    EtatPays _etat;
    int _compteurEtat;
    int _maxProductionRessource;
    int _ressourceDispo;
    vector<Pays *> _alliance;

private:
    static int _tempsAccord;
    static int _tempsGuerre;

public:
    Pays(int idPays, string nom,
         int religion,
         RessourceBase ressource,
         EtatPays etat = EtatPays::Neutre);

    ~Pays() = default;

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

private:
    void actualiserEtat();
    void guerreDeclaree(Pays &pays);
};

#endif
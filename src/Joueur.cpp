#include "Joueur.hpp"

const int Joueur::_stockRBMax = 5;
const int Joueur::_stockRCMax = 5;

const int Joueur::_coupAttaqueArmee = 2;
const int Joueur::_coupAttaqueReligion = 2;
const int Joueur::_coupAccordCommercial = 2;
const int Joueur::_coupConvertir = 1;
const int Joueur::_coupTransformer = 3;

Joueur::Joueur(Pays *paysJoueur)
    : _ptAction(0),
      _paysPossedes{paysJoueur}
{
    // Mise a 0 des ressources
    for (int i = 0; i < 9; i++)
        _stockRB[i] = 0;
    for (int i = 0; i < 3; i++)
        _stockRC[i] = 0;
}

Joueur::~Joueur()
{
}

// Retourne le stock de la i eme RB
// Retourne -1 si en dehors des la tableau
int Joueur::getStockRBi(int i)
{
    int stock = -1;
    if (i >= 0 && i < 9)
        stock = _stockRB[i];

    return stock;
}

// Retourne le stock de la i eme RC
// Retourne -1 si en dehors des la tableau
int Joueur::getStockRCi(int i)
{
    int stock = -1;
    if (i >= 0 && i < 3)
        stock = _stockRC[i];

    return stock;
}

// Donne 5 points d'actions au joueur
void Joueur::donnerPointAction(int pt)
{
    _ptAction = pt;
}

// Essaye de faire un accord commercial avec un pays
string Joueur::accordCommercial(Pays &pays)
{
    string message;

    if (pays.accordCommercial())
    {
        message += "Accord commercial établi. ";
        message += "(" + to_string(pays.getCompteur()) + ") ";
        message += "Vous ressource disponible pour 1 point d'action.";
    }
    else
    {
        message += "Acccord commercial échec. ";
        message += "Pays en guerre contre vous. ";
    }

    return message;
}

// Convertir la population du pays
// Renvoie un message d'info
// Utilise ressource : RB2 => 10%
// Utilise ressource : RC2 => 25%
string Joueur::convertir(Pays &pays)
{
    int indiceRB = static_cast<int>(RessourceBase::RB2);
    int indiceRC = static_cast<int>(RessourceCraft::RC2);

    string message;
    int tauxConversion = 0;

    // Stock Ressource Base > 0
    if (_stockRB[indiceRB])
    {
        _stockRB[indiceRB]--; // Reduit le stock
        tauxConversion += 10; // Augmente le taux
    }

    // Stock Ressource Craft > 0
    if (_stockRC[indiceRC])
    {
        _stockRC[indiceRC]--; // Reduit le stock
        tauxConversion += 25; // Augmente le taux
    }

    // Message de l'action
    if (tauxConversion > 0)
    {
        _ptAction -= _coupConvertir; // Utilisation des points d'actions

        // Conversion du pays
        bool conversionTotal = pays.convertir(tauxConversion);
        if (conversionTotal)
        {
            message += "Pays totalement converti.";
            message += "Vous pouvez tenter une OPC (Offre Publique de Conversion)";
        }
        else
        {
            message += to_string(tauxConversion * 10);
            message += "%% de personne converti";
        }
    }
    else
    { // Echec de la conversion
        message += "Pas assez de ressource pour convertir la population.";
    }

    return message;
}

// Attaque d'un pays
// Renvoie un message d'info
// Utilise ressource : RB0 => 15%
// Utilise ressource : RB1 => 15%
// Utilise ressource : RC0 => 35%
// Utilise ressource : RC1 => 35%
string Joueur::attaqueArmee(Pays &pays)
{
    int indiceRB0 = static_cast<int>(RessourceBase::RB0);
    int indiceRB1 = static_cast<int>(RessourceBase::RB1);
    int indiceRC0 = static_cast<int>(RessourceCraft::RC0);
    int indiceRC1 = static_cast<int>(RessourceCraft::RC1);

    string message;
    int probaReussite = 0;

    // Stock Ressource Base > 0
    if (_stockRB[indiceRB0])
    {
        _stockRB[indiceRB0]--; // Reduit le stock
        probaReussite += 15;   // Augmente la proba de reussite
    }
    if (_stockRB[indiceRB1])
    {
        _stockRB[indiceRB1]--; // Reduit le stock
        probaReussite += 15;   // Augmente la proba de reussite
    }

    // Stock Ressource Craft > 0
    if (_stockRC[indiceRC0])
    {
        _stockRC[indiceRC0]--; // Reduit le stock
        probaReussite += 35;   // Augmente la proba de reussite
    }
    if (_stockRC[indiceRC1])
    {
        _stockRC[indiceRC1]--; // Reduit le stock
        probaReussite += 35;   // Augmente la proba de reussite
    }

    // Consomme un point d'action
    _ptAction -= _coupAttaqueArmee;

    if (rand() % 100 <= probaReussite)
    { // Attaque reussite

        annexerPays(pays);

        message += "Pays capturé !";
    }
    else
    { // Echec de l'attaque
        message += "Pas assez puissant, il faut avoir plus de ressources differentes.";
    }
    return message;
}

// Attaque religion
string Joueur::attaqueReligion(Pays &pays)
{
    string message;
    int populationFidele = pays.getPopFidele();

    if (rand() % 100 < populationFidele)
    { // Conversion réussite
        annexerPays(pays);

        message += "OPC (Offre Publique de Conversion) réussite.";
    }
    else
    { // Echec de la conversion
        message += "La religion n'a pas assez de charisme.";
    }

    return message;
}

// Annexe un pays et ajout dans la liste
void Joueur::annexerPays(Pays &pays)
{
    pays.annexer();                 // Annexe le pays
    _paysPossedes.push_back(&pays); // Ajout a la liste des pays annexes
}

// Nouveau Tour joueur
void Joueur::nouveauTour()
{
    // Reset les pt d'actions
    donnerPointAction();

    // Récupère les ressources
    int indiceRB;
    for (auto p : _paysPossedes)
    {
        indiceRB = static_cast<int>(p->getRessource());
        // Recupere toute la capacite de prod des pays
        for (int k = 0; k < p->getMaxProduction(); ++k)
        {
            _stockRB[indiceRB] = (_stockRB[indiceRB] + 1 < _stockRBMax);
        }
    }
}

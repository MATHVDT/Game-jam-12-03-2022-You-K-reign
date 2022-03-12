#include "Pays.hpp"

Pays::Pays(int idPays, string nom,
           int religion,
           RessourceBase ressource,
           EtatPays etat)
    : _idPays(idPays), _nomPays(nom),
      _religion(religion),
      _ressource(ressource), _etat(etat),
      // texture
      _compteurEtat(0),
      _maxProductionRessource(3),
      _ressourceDispo(0),
      _alliance()

{
}

void Pays::nouveauTour()
{
    actualiserEtat();

    // Produit ses ressources
    _ressourceDispo = _maxProductionRessource;
}

// Regarde s'il les accords/guerre tj en cours
void Pays::actualiserEtat()
{
    if (_compteurEtat == 0)
    {
        _etat = EtatPays::Neutre;
    }
    else
    {
        --_compteurEtat;
    }
}

// Pays annexe et donc les pays de l'alliance
// pas encore annexe passe en guerre
void Pays::annexer()
{
    // Passe le pays en annexe
    _etat = EtatPays::Annexe;

    // Tous les pays de alliance => guerre
    for (auto pays : _alliance)
    {
        guerreDeclaree(*pays);
    }
}

// Pays passe en guerre
void Pays::guerreDeclaree(Pays &pays)
{
    // S'il est deja annexe alors rien
    if (pays._etat == EtatPays::Annexe)
        return;

    // Passe le pays en guerre
    pays._etat = EtatPays::Guerre;
    pays._compteurEtat = _tempsGuerre;
}

// Tente de mettre un accord commercial
bool Pays::accordCommercial()
{
    if (_etat == EtatPays::Guerre)
        return false;

    // Passe le pays en accord commercial
    _etat = EtatPays::Accord;
    _compteurEtat += _tempsAccord;
}

// Vendre une ressource au joueur
RessourceBase Pays::vendreRessource(int &ptActionJoueur)
{
    RessourceBase r = _ressource;

    switch (_etat)
    {
    case EtatPays::Accord:
        ptActionJoueur -= 1;
        break;
    case EtatPays::Neutre:
        ptActionJoueur -= 2;
        break;
    case EtatPays::Guerre:
    case EtatPays::Annexe:
        r = RessourceBase::RIEN;
        break;
    default:
        cerr << "Vendre ressource mais l'etat du pays est bizarre";
        break;
    }
    return r;
}
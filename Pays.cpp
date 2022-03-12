#include "Pays.hpp"

int Pays::_tempsAccord = 3;
int Pays::_tempsGuerre = 5;

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

void Pays::afficherConsole()
{
    cout << endl;
    cout << "id pays : " << _idPays << endl;
    cout << "nom pays : " << _nomPays << endl;
    cout << "religion : " << _religion << endl;
    cout << "ressource : " << static_cast<int>(_ressource) << endl;

    // Texture SDL2 _texture

    cout << "etat : " << static_cast<int>(_etat) << endl;
    cout << "compteur etat : " << _compteurEtat << endl;
    cout << "max prod : " << _maxProductionRessource << endl;
    cout << "ressource dispo : " << _ressourceDispo << endl;
    // vector<Pays *> _alliance;
}

// Check l'etat du pays et remet
// les stocks a 0 en debut de tour
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

    // Reduit la production
    _maxProductionRessource = 2;

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

    return true;
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

// Convertir un pays
// Prend un taux de conversion definit
void Pays::convertir(int tauxConversion)
{
    _religion += tauxConversion;
    if (_religion > 10)
        _religion = 10;
}

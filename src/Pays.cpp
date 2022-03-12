#include "Pays.hpp"
#include "dessin.hpp" 

int Pays::_tempsAccord = 3;
int Pays::_tempsGuerre = 5;

double Pays::_angle[9];
SDL_Texture *Pays::_textureIle;
SDL_Texture *Pays::_textureEtat[3];
SDL_Texture *Pays::_textureRessourcesCraft[3];
SDL_Texture *Pays::_textureRessourcesBase[9];

Pays::Pays(int idPays, string nom,
           int religion,
           RessourceBase ressource,
           EtatPays etat)
    : _idPays(idPays), _nomPays(nom),
      _religion(religion),
      _ressource(ressource), _etat(etat),
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

void Pays::afficherPays(SDL_Renderer * renderer)
{
    dessinerIle(renderer,_textureIle,_angle,_idPays);
    dessinerRessource(renderer,_textureRessourcesBase,static_cast<int>(_ressource),_idPays);
    if (static_cast<int>(_etat) != 0)
    {
        dessinerEtat(renderer,_textureEtat,static_cast<int>(_etat),_idPays);
    }
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
// Retourne false si pas d'accord car guerre
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
        ptActionJoueur -= 1; // ...
        break;
    case EtatPays::Neutre:
        ptActionJoueur -= 2; // ...
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
// Renvoie true si le pays est totalement converti
bool Pays::convertir(int tauxConversion)
{
    bool conversionTotale = false;

    _religion += tauxConversion;

    if (_religion > 100)
    {
        conversionTotale = true;
        _religion = 100;
    }

    return conversionTotale;
}

// Charger Texture SDL2

void Pays::chargerTexture(SDL_Renderer *renderer)
{
    int tab[4] = {90, 180, 270, 0};
    for (int i = 0; i < 9; i++)
    {
        Pays::_angle[i] = tab[rand() % 4];
    }
    
    //Charger Texture Ile

    SDL_Surface *imagesIle;
    
    imagesIle = IMG_Load("../img/fond_ile.png");

    _textureIle = SDL_CreateTextureFromSurface(renderer, imagesIle);
    SDL_FreeSurface(imagesIle);

    SDL_Surface *imagesEtat[3];

    imagesEtat[0] = IMG_Load("../img/en_guerre.png");
    imagesEtat[1] = IMG_Load("../img/accord_commercial.png");
    imagesEtat[2] = IMG_Load("../img/conquis.png");

    for (int i = 0; i < 3; i++)
    {
        _textureEtat[i] = SDL_CreateTextureFromSurface(renderer, imagesEtat[i]);
        SDL_FreeSurface(imagesEtat[i]);
    }

    SDL_Surface *imagesRessourcesBase[9];
    
    imagesRessourcesBase[0] = IMG_Load("../img/ressources/ressource_1.png");
    imagesRessourcesBase[1] = IMG_Load("../img/ressources/ressource_2.png");
    imagesRessourcesBase[2] = IMG_Load("../img/ressources/ressource_3.png");
    imagesRessourcesBase[3] = IMG_Load("../img/ressources/ressource_4.png");
    imagesRessourcesBase[4] = IMG_Load("../img/ressources/ressource_5.png");
    imagesRessourcesBase[5] = IMG_Load("../img/ressources/ressource_6.png");
    imagesRessourcesBase[6] = IMG_Load("../img/ressources/ressource_7.png");
    imagesRessourcesBase[7] = IMG_Load("../img/ressources/ressource_8.png");
    imagesRessourcesBase[8] = IMG_Load("../img/ressources/ressource_9.png");

    for (int i = 0; i < 9; i++)
    {
        _textureRessourcesBase[i] = SDL_CreateTextureFromSurface(renderer, imagesRessourcesBase[i]);
        SDL_FreeSurface(imagesRessourcesBase[i]);
    }

    SDL_Surface *imagesRessourcesCraft[3];

    imagesRessourcesCraft[0] = IMG_Load("../img/ressources_craft/ressource__craft_1.png");
    imagesRessourcesCraft[1] = IMG_Load("../img/ressources_craft/ressource__craft_2.png");
    imagesRessourcesCraft[2] = IMG_Load("../img/ressources_craft/ressource__craft_3.png");

    for (int i = 0; i < 3; i++)
    {
        _textureRessourcesCraft[i] = SDL_CreateTextureFromSurface(renderer, imagesRessourcesCraft[i]);
        SDL_FreeSurface(imagesRessourcesCraft[i]);
    }
}

void Pays::detruireTexture()
{
    SDL_DestroyTexture(_textureIle);

    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(_textureEtat[i]);
        SDL_DestroyTexture(_textureRessourcesCraft[i]);
    }

    for (int i = 0; i < 9; i++)
    {
        SDL_DestroyTexture(_textureRessourcesBase[i]);
    }
}

/*
Faire fonction dessinerReligion
Faire en sorte d'avoir un numéro à coté de la ressource
*/
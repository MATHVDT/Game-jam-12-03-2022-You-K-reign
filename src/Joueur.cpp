#include "Joueur.hpp"

const int Joueur::_stockRBMax = 3;
const int Joueur::_stockRCMax = 3;

const int Joueur::_coupAttaqueArmee = 2;
const int Joueur::_coupAttaqueReligion = 2;
const int Joueur::_coupAccordCommercial = 2;
const int Joueur::_coupConvertir = 1;
const int Joueur::_coupTransformer = 3;

SDL_Texture *Joueur::_textureRessources[8];

Joueur::Joueur(Pays *paysJoueur)
    : _pays(paysJoueur), _ptAction(0),
      _paysAnnexes()
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
    {                   // Attaque reussite
        pays.annexer(); // Annexe le pays

        _paysAnnexes.push_back(&pays); // Ajout a la liste des pays annexes

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
        pays.annexer();

        _paysAnnexes.push_back(&pays);

        message += "OPC (Offre Publique de Conversion) réussite.";
    }
    else
    { // Echec de la conversion
        message += "La religion n'a pas assez de charisme.";
    }

    return message;
}

void Joueur::chargerTexture(SDL_Renderer *renderer)
{
    TTF_Font *font = TTF_OpenFont("arial.ttf", 20);

    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
    }

    SDL_Surface *imagesRessources[8];

    imagesRessources[0] = TTF_RenderText_Blended(font, "0", SDL_Color{0, 0, 0, 250});
    imagesRessources[1] = TTF_RenderText_Blended(font, "1", SDL_Color{0, 0, 0, 250});
    imagesRessources[2] = TTF_RenderText_Blended(font, "2", SDL_Color{0, 0, 0, 250});
    imagesRessources[3] = TTF_RenderText_Blended(font, "3", SDL_Color{0, 0, 0, 250});
    imagesRessources[4] = TTF_RenderText_Blended(font, "4", SDL_Color{0, 0, 0, 250});
    imagesRessources[5] = TTF_RenderText_Blended(font, "5", SDL_Color{0, 0, 0, 250});
    imagesRessources[6] = TTF_RenderText_Blended(font, "/", SDL_Color{0, 0, 0, 250});
    imagesRessources[7] = TTF_RenderText_Blended(font, "PA :", SDL_Color{0, 0, 0, 250});

    for (int i = 0; i < 8; i++)
    {
        _textureRessources[i] = SDL_CreateTextureFromSurface(renderer, imagesRessources[i]);
        SDL_FreeSurface(imagesRessources[i]);
    }

    TTF_CloseFont(font);
}

void Joueur::detruireTexture()
{
    for (int i = 0; i < 8; i++)
    {
        SDL_DestroyTexture(_textureRessources[i]);
    }
}

void Joueur::afficherJoueur(SDL_Renderer *renderer)
{
    for (int i = 0; i < 9; i++)
    {
        dessinerRessourcePrimaire(renderer, _textureRessources, i, _stockRB[i], _stockRBMax);
    }
    for (int i = 0; i < 3; i++)
    {
        dessinerRessourceSecondaire(renderer, _textureRessources, i, _stockRC[i], _stockRCMax);
    }

    dessinerPARestant(renderer, _textureRessources, getPtAction());
}

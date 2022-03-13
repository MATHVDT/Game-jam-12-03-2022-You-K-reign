#include "Joueur.hpp"

const int Joueur::_stockRBMax = 5;
const int Joueur::_stockRCMax = 5;

const int Joueur::_coupAttaqueArmee = 2;
const int Joueur::_coupAttaqueReligion = 2;
const int Joueur::_coupAccordCommercial = 2;
const int Joueur::_coupAcheterRessource = 2;
const int Joueur::_coupAcheterRessourceAccord = 1;
const int Joueur::_coupConvertir = 1;
const int Joueur::_coupTransformer = 3;

SDL_Texture *Joueur::_textureRessources[7];

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

// Retourne le pays d'origine
Pays *Joueur::getPaysOrigin()
{
    int k = 0;
    bool origin = false;
    while (!origin && k < (int)_paysPossedes.size())
    {
        origin = _paysPossedes.at(k)->getEtatPays() == EtatPays::Neutre;
        ++k;
    }

    return _paysPossedes.at(k - 1);
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

    if (pays.getPopFidele() == 100)
    {
        message += "La population est deja convertie.";
        message += " Vous voulez pas pas qu'elle vous adore en plus ?";
    }
    else
    {
        if (checkAssezPtAction(_coupConvertir, message))
        { // Assez de PA
            if (_stockRB[indiceRB])
            {                         // Stock Ressource Base > 0
                _stockRB[indiceRB]--; // Reduit le stock
                tauxConversion += 10; // Augmente le taux
            }

            if (_stockRC[indiceRC])
            {                         // Stock Ressource Craft > 0
                _stockRC[indiceRC]--; // Reduit le stock
                tauxConversion += 25; // Augmente le taux
            }

            // Test au moins 1 ressource => tauxConversion > 0
            if (checkAssezRessource(tauxConversion, message))
            {
                // Conversion du pays
                bool conversionTotal = pays.convertir(tauxConversion);
                if (conversionTotal)
                {
                    message += "Pays totalement converti.";
                    message += "Vous pouvez tenter une OPC (Offre Publique de Conversion)";
                }
                else
                {
                    message += "+" + to_string(tauxConversion);
                    message += "\% de personnes converti";
                }
            }
        }
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

    if (checkAssezPtAction(_coupAttaqueArmee, message))
    { // Test assez de PA
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
        // Test au moins 1 ressource => probReussite > 0
        if (checkAssezRessource(probaReussite, message))
        {
            int r = rand() % 100;
            // cerr << "random : " << r << " proba : " << probaReussite << endl;
            if (r <= probaReussite)
            { // Attaque reussite
                annexerPays(pays);
                message += "Pays capturé !";
            }
            else
            { // Echec de l'attaque
                message += "Pas assez puissant, il faut avoir plus de ressources differentes.";
            }
        }
    }
    return message;
}

// Attaque religion
string Joueur::attaqueReligion(Pays &pays)
{
    string message;
    int populationFidele = pays.getPopFidele();

    // Test assez de PA
    if (checkAssezPtAction(_coupAttaqueArmee, message))
    {
        int r = rand() % 100;
        // cerr << "random : " << r << " populationFidele : " << populationFidele << endl;
        if (r < populationFidele)
        { // Conversion réussite
            annexerPays(pays);

            message += "OPC (Offre Publique de Conversion) réussite.";
        }
        else
        { // Echec de la conversion
            message += "La religion n'a pas assez de charisme.";
        }
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
// Donne des points d'actions
// Collecte les resssources des pays possedes
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
            _stockRB[indiceRB] += (_stockRB[indiceRB] + 1 < _stockRBMax);
        }
    }
}

// Achete une ressource a un pays
string Joueur::acheter(Pays &pays)
{
    string message;

    EtatPays etatPays = pays.getEtatPays();

    switch (etatPays)
    {
    case EtatPays::Accord:
        message += acheterRessourcePaysAccord(pays);
        break;
    case EtatPays::Neutre:
        message += acheterRessourcePaysNeutre(pays);
        break;
    case EtatPays::Guerre:
        message += "Ile en guerre, vous ne pouvez pas acheter de ressource.";
        break;
    case EtatPays::Annexe:
        message += "Vous possedez déjà l'ile et la ressource.";
        break;
    default:
        message += "Etat du pays bizarre, surement des indépendantistes.";
        cerr << message;
        break;
    }
    return message;
}

// Achete la ressource au prix d'un pays neutre
string Joueur::acheterRessourcePaysNeutre(Pays &pays)
{
    string message;
    int indiceRB = static_cast<int>(pays.getRessource());
    if (_stockRB[indiceRB] + 1 <= _stockRBMax)
    {
        // Verifie s'il ya encore des truc a acheter
        if (pays.getRessourceDispo() > 0)
        { // Check si ya de la place dans le stock
            // Check s'il peut agir
            if (checkAssezPtAction(_coupAcheterRessource, message))
            {
                _stockRB[indiceRB]++; // Augmente la ressource
                pays.vendreRessource();
                message += "Ressource achetée. Victoire du capitalisme.";
            }
        }
        else
        {
            message += "Vous avez tous acheté. C'est comme le PQ pendant le covid, rupture de stock.";
        }
    }
    else
    {
        message += "Plus d'espace disponible pour cette ressource.";
    }

    return message;
}

// Achete la ressource au prix d'un pays avec accord commercial
string Joueur::acheterRessourcePaysAccord(Pays &pays)
{
    string message;
    // Check s'il peut agir
    int indiceRB = static_cast<int>(pays.getRessource());
    if (_stockRB[indiceRB] + 1 <= _stockRBMax)
    { // Check si ya de la place dans le stock
        if (pays.getRessourceDispo() > 0)
        { // Verifie s'il ya encore des truc a acheter
            if (checkAssezPtAction(_coupAcheterRessourceAccord, message))
            {
                _stockRB[indiceRB]++; // Augmente la ressource
                pays.vendreRessource();
                message += "Ressource achetée pour 1 Action. STONKS ↗";
            }
        }
        else
        {
            message += "Vous avez tous acheté. C'est comme le PQ pendant le covid, rupture de stock.";
        }
    }
    else
    {
        message += "Plus d'espace disponible pour cette ressource.";
    }

    return message;
}

// Check si le joueur a assez de pas en fct du coup
// Et consomme les PA necessaire
bool Joueur::checkAssezPtAction(int coup, string &message)
{
    bool peutAgir;
    if (_ptAction - coup >= 0)
    {
        peutAgir = true;
        _ptAction -= coup;
    }
    else
    {
        peutAgir = false;
        message += "Pas assez de points d'action.";
    }
    return peutAgir;
}

// Check si le joueur a assez de ressource
// Regarde en faite si le % est > 0
bool Joueur::checkAssezRessource(int pourcentage, string &message)
{
    int assezRessource;
    if (pourcentage > 0)
    {
        assezRessource = true;
    }
    else
    {
        assezRessource = false;
        message += "Pas assez de points d'action.";
    }
    return assezRessource;
}

// Transforme toutes les RB possible en RC
// RB3 + R4 => RC0
// RB5 + R6 => RC1
// RB7 + R8 => RC3
string Joueur::transformerRessource()
{
    string message;

    if (checkAssezPtAction(_coupTransformer, message))
    { // Assez de PA
        int nbRessourceCraft = 0;
        // RB3 + R4 => RC0
        while ((_stockRC[0] + 1 <= _stockRBMax) &&
               _stockRB[3] && _stockRB[4])
        {
            _stockRC[0]++;
            _stockRB[3]--;
            _stockRB[4]--;
            nbRessourceCraft++;
        }

        // RB5 + R6 => RC1
        while ((_stockRC[1] + 1 <= _stockRBMax) &&
               _stockRB[5] && _stockRB[6])
        {
            _stockRC[1]++;
            _stockRB[5]--;
            _stockRB[6]--;
            nbRessourceCraft++;
        }

        // RB7 + R8 => RC2
        while ((_stockRC[2] + 1 <= _stockRBMax) &&
               _stockRB[7] && _stockRB[8])
        {
            _stockRC[2]++;
            _stockRB[7]--;
            _stockRB[8]--;
            nbRessourceCraft++;
        }

        message = to_string(nbRessourceCraft) + " resssources transformées.";
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

    SDL_Surface *imagesRessources[7];

    imagesRessources[0] = TTF_RenderText_Blended(font, "0", SDL_Color{0, 0, 0, 250});
    imagesRessources[1] = TTF_RenderText_Blended(font, "1", SDL_Color{0, 0, 0, 250});
    imagesRessources[2] = TTF_RenderText_Blended(font, "2", SDL_Color{0, 0, 0, 250});
    imagesRessources[3] = TTF_RenderText_Blended(font, "3", SDL_Color{0, 0, 0, 250});
    imagesRessources[4] = TTF_RenderText_Blended(font, "4", SDL_Color{0, 0, 0, 250});
    imagesRessources[5] = TTF_RenderText_Blended(font, "5", SDL_Color{0, 0, 0, 250});
    imagesRessources[6] = TTF_RenderText_Blended(font, "/", SDL_Color{0, 0, 0, 250});

    for (int i = 0; i < 7; i++)
    {
        _textureRessources[i] = SDL_CreateTextureFromSurface(renderer, imagesRessources[i]);
        SDL_FreeSurface(imagesRessources[i]);
    }

    TTF_CloseFont(font);
}

void Joueur::detruireTexture()
{
    for (int i = 0; i < 7; i++)
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
}

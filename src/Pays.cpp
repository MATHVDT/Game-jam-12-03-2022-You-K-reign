#include "Pays.hpp"

int Pays::_tempsAccord = 3;
int Pays::_tempsGuerre = 5;

double Pays::_angle[9];
SDL_Texture *Pays::_textureIle;
SDL_Texture *Pays::_textureEtat[3];
SDL_Texture *Pays::_textureRessourcesCraft[3];
SDL_Texture *Pays::_textureRessourcesBase[15];
SDL_Texture *Pays::_textureText[21];
SDL_Texture *Pays::_textureVille[9];

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

Pays::~Pays()
{
    // cout << "Destructeur Pays" << endl;
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

void Pays::afficherPays(SDL_Renderer *renderer)
{
    dessinerIle(renderer, _textureIle, _angle, _idPays);

    // dessinerVille(renderer, _textureVille, _idPays);

    dessinerRessource(renderer, _textureRessourcesBase, static_cast<int>(_ressource), _idPays, _ressourceDispo);

    if (static_cast<int>(_etat) != 0)
    {
        dessinerEtat(renderer, _textureEtat, static_cast<int>(_etat), _idPays);
    }
    dessinerReligion(renderer, _textureText, static_cast<int>(_religion), _idPays);
}

// Check l'etat du pays et remet
// les stocks a 0 en debut de tour
void Pays::nouveauTour()
{
    if (_etat != EtatPays::Annexe)
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

    // Reduit la production
    _maxProductionRessource = 2;

    // Tous les pays de alliance => guerre
    for (auto pays : _alliance)
    {
        if (pays->getEtatPays() != EtatPays::Guerre)
            guerreDeclaree(*pays);
    }
    // Passe le pays en annexe
    _etat = EtatPays::Annexe;
}

// Pays passe en guerre
void Pays::guerreDeclaree(Pays &pays)
{
    // S'il est deja annexe alors rien
    if (pays._etat != EtatPays::Annexe)
    {
        // Passe le pays en guerre
        pays._etat = EtatPays::Guerre;
        pays._compteurEtat = _tempsGuerre;
    }
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
void Pays::vendreRessource()
{
    _ressourceDispo--;
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
    TTF_Font *font = TTF_OpenFont("arial.ttf", 20);

    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
    }

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

    SDL_Surface *imagesRessourcesBase[15];

    imagesRessourcesBase[0] = IMG_Load("../img/ressources/ressource_1.png");
    imagesRessourcesBase[1] = IMG_Load("../img/ressources/ressource_2.png");
    imagesRessourcesBase[2] = IMG_Load("../img/ressources/ressource_3.png");
    imagesRessourcesBase[3] = IMG_Load("../img/ressources/ressource_4.png");
    imagesRessourcesBase[4] = IMG_Load("../img/ressources/ressource_5.png");
    imagesRessourcesBase[5] = IMG_Load("../img/ressources/ressource_6.png");
    imagesRessourcesBase[6] = IMG_Load("../img/ressources/ressource_7.png");
    imagesRessourcesBase[7] = IMG_Load("../img/ressources/ressource_8.png");
    imagesRessourcesBase[8] = IMG_Load("../img/ressources/ressource_9.png");
    imagesRessourcesBase[9] = TTF_RenderText_Blended(font, "0 x ", SDL_Color{0, 0, 0, 250});
    imagesRessourcesBase[10] = TTF_RenderText_Blended(font, "1 x ", SDL_Color{0, 0, 0, 250});
    imagesRessourcesBase[11] = TTF_RenderText_Blended(font, "2 x ", SDL_Color{0, 0, 0, 250});
    imagesRessourcesBase[12] = TTF_RenderText_Blended(font, "3 x ", SDL_Color{0, 0, 0, 250});
    imagesRessourcesBase[13] = TTF_RenderText_Blended(font, "4 x ", SDL_Color{0, 0, 0, 250});
    imagesRessourcesBase[14] = TTF_RenderText_Blended(font, "5 x ", SDL_Color{0, 0, 0, 250});

    for (int i = 0; i < 15; i++)
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

    SDL_Surface *textes[21];

    textes[0] = TTF_RenderText_Blended(font, "0%", SDL_Color{0, 0, 0, 250});
    textes[1] = TTF_RenderText_Blended(font, "5%", SDL_Color{0, 0, 0, 250});
    textes[2] = TTF_RenderText_Blended(font, "10%", SDL_Color{0, 0, 0, 250});
    textes[3] = TTF_RenderText_Blended(font, "15%", SDL_Color{0, 0, 0, 250});
    textes[4] = TTF_RenderText_Blended(font, "20%", SDL_Color{0, 0, 0, 250});
    textes[5] = TTF_RenderText_Blended(font, "25%", SDL_Color{0, 0, 0, 250});
    textes[6] = TTF_RenderText_Blended(font, "30%", SDL_Color{0, 0, 0, 250});
    textes[7] = TTF_RenderText_Blended(font, "35%", SDL_Color{0, 0, 0, 250});
    textes[8] = TTF_RenderText_Blended(font, "40%", SDL_Color{0, 0, 0, 250});
    textes[9] = TTF_RenderText_Blended(font, "45%", SDL_Color{0, 0, 0, 250});
    textes[10] = TTF_RenderText_Blended(font, "50%", SDL_Color{0, 0, 0, 250});
    textes[11] = TTF_RenderText_Blended(font, "55%", SDL_Color{0, 0, 0, 250});
    textes[12] = TTF_RenderText_Blended(font, "60%", SDL_Color{0, 0, 0, 250});
    textes[13] = TTF_RenderText_Blended(font, "65%", SDL_Color{0, 0, 0, 250});
    textes[14] = TTF_RenderText_Blended(font, "70%", SDL_Color{0, 0, 0, 250});
    textes[15] = TTF_RenderText_Blended(font, "75%", SDL_Color{0, 0, 0, 250});
    textes[16] = TTF_RenderText_Blended(font, "80%", SDL_Color{0, 0, 0, 250});
    textes[17] = TTF_RenderText_Blended(font, "85%", SDL_Color{0, 0, 0, 250});
    textes[18] = TTF_RenderText_Blended(font, "90%", SDL_Color{0, 0, 0, 250});
    textes[19] = TTF_RenderText_Blended(font, "95%", SDL_Color{0, 0, 0, 250});
    textes[20] = TTF_RenderText_Blended(font, "100%", SDL_Color{0, 0, 0, 250});

    for (int i = 0; i < 21; i++)
    {
        _textureText[i] = SDL_CreateTextureFromSurface(renderer, textes[i]);
        SDL_FreeSurface(textes[i]);
    }

    TTF_CloseFont(font);

    // Image ville
    // SDL_Surface *imagesVille[9];

    // imagesVille[0] = IMG_Load("../img/maison.png");
    // imagesVille[1] = IMG_Load("../img/maison.png");
    // imagesVille[2] = IMG_Load("../img/maison.png");
    // imagesVille[3] = IMG_Load("../img/maison.png");
    // imagesVille[4] = IMG_Load("../img/maison.png");
    // imagesVille[5] = IMG_Load("../img/maison.png");
    // imagesVille[6] = IMG_Load("../img/maison.png");
    // imagesVille[7] = IMG_Load("../img/maison.png");
    // imagesVille[8] = IMG_Load("../img/maison.png");

    // for (int i = 0; i < 9; i++)
    // {
    //     _textureVille[i] = SDL_CreateTextureFromSurface(renderer, imagesVile[i]);
    //     SDL_FreeSurface(imagesVile[i]);
    // }
}

void Pays::detruireTexture()
{
    SDL_DestroyTexture(_textureIle);

    for (int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(_textureEtat[i]);
        SDL_DestroyTexture(_textureRessourcesCraft[i]);
    }

    for (int i = 0; i < 15; i++)
    {
        SDL_DestroyTexture(_textureRessourcesBase[i]);
    }

    for (int i = 0; i < 21; i++)
    {
        SDL_DestroyTexture(_textureText[i]);
    }
}

/*
Faire fonction dessinerReligion
Faire en sorte d'avoir un numéro à coté de la ressource
*/
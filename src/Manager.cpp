#include "Manager.hpp"

Manager::Manager()
{
    _textureMenuFond = nullptr;
    _textureFondInterface = nullptr;
    _textureRessourcesInterface = nullptr;

    for (int i = 0; i < 9; i++)
    {
        _tabPays[i] = nullptr;
    }

    for (int i = 0; i < 6; i++)
    {
        _tabBouton[i] = nullptr;
    }
}

Manager::~Manager()
{
    detruireTexture();

    for (int i = 0; i < 9; i++)
    {
        delete _tabPays[i];
    }

    for (int i = 0; i < 6; i++)
    {
        delete _tabBouton[i];
    }
}

void Manager::initJeu(SDL_Renderer *renderer)
{
    chargerTexture(renderer);
    initPays();
    initBouton();
    _joueur = Joueur();
    initJoueur(_tabPays[4]);
    creerAlliance();
}

void Manager::chargerTexture(SDL_Renderer *renderer)
{
    // Menu de jeu
    _menu.setPosition(450, 240);

    SDL_Color hoverColor = {141, 88, 36, 250};
    SDL_Color normalColor = {250, 197, 129, 250};
    _menu.setColor(normalColor, hoverColor);

    _menu.chargerTexture(renderer, "Jouer");
    _menu.chargerTexture(renderer, "Instructions");
    _menu.chargerTexture(renderer, "Credits");
    _menu.chargerTexture(renderer, "Quitter");

    // Charger texture jeu
    Pays::chargerTexture(renderer);
    Bouton::chargerTexture(renderer);
    Joueur::chargerTexture(renderer);

    // Charger Texture Menu Fond

    SDL_Surface *imageMenuFond;

    imageMenuFond = IMG_Load("../img/menu.png");

    _textureMenuFond = SDL_CreateTextureFromSurface(renderer, imageMenuFond);
    SDL_FreeSurface(imageMenuFond);

    // Charger Texture Interface Ressource
    SDL_Surface *imageRessourceInterface;

    imageRessourceInterface = IMG_Load("../img/menu/interface_ressource_verticale.png");

    _textureRessourcesInterface = SDL_CreateTextureFromSurface(renderer, imageRessourceInterface);
    SDL_FreeSurface(imageRessourceInterface);

    //Charger Texture Fond Interface
    SDL_Surface *imageFondInterface;

    imageFondInterface = IMG_Load("../img/fond_menu.png");

    _textureFondInterface = SDL_CreateTextureFromSurface(renderer, imageFondInterface);
    SDL_FreeSurface(imageFondInterface);
}

void Manager::detruireTexture()
{
    SDL_DestroyTexture(_textureMenuFond);
    SDL_DestroyTexture(_textureFondInterface);
    SDL_DestroyTexture(_textureRessourcesInterface);
    Bouton::detruireTexture();
    Pays::detruireTexture();
    Joueur::detruireTexture();
}

void Manager::initPays()
{
    _tabPays[0] = new Pays(0, "Ukraine", 10, RessourceBase::RB0, EtatPays::Neutre);
    _tabPays[1] = new Pays(1, "Russie", 15, RessourceBase::RB1, EtatPays::Neutre);
    _tabPays[2] = new Pays(2, "Serbie", 5, RessourceBase::RB2, EtatPays::Neutre);
    _tabPays[3] = new Pays(3, "Bosnie", 10, RessourceBase::RB3, EtatPays::Neutre);
    _tabPays[4] = new Pays(4, "Slovaquie", 100, RessourceBase::RB4, EtatPays::Neutre);
    _tabPays[5] = new Pays(5, "Pologne", 15, RessourceBase::RB5, EtatPays::Neutre);
    _tabPays[6] = new Pays(6, "Chypre", 20, RessourceBase::RB6, EtatPays::Neutre);
    _tabPays[7] = new Pays(7, "Malte", 5, RessourceBase::RB7, EtatPays::Neutre);
    _tabPays[8] = new Pays(8, "Corse", 0, RessourceBase::RB8, EtatPays::Neutre);
}

void Manager::initJoueur(Pays *paysJoueur)
{
    _joueur.initJoueur(paysJoueur);
}

void Manager::initBouton()
{
    _tabBouton[0] = new Bouton(0, false);
    _tabBouton[1] = new Bouton(1, false);
    _tabBouton[2] = new Bouton(2, false);
    _tabBouton[3] = new Bouton(3, false);
    _tabBouton[4] = new Bouton(4, false);
    _tabBouton[5] = new Bouton(5, false);
}

void Manager::afficher(SDL_Renderer *renderer)
{
    SDL_Rect srcFondInterface{0, 0, 0, 0};
    SDL_Rect srcRessourcesInterface{0, 0, 0, 0};
    SDL_Rect srcFondInterface2{0,0,0,0};
    SDL_Rect dstFondInterface{600, 0, 365, 600};
    SDL_Rect dstRessourcesInterface{965, 0, 120, 600};
    SDL_Rect dstFondInterface2{1085, 0, 15, 600};

    SDL_QueryTexture(_textureFondInterface, nullptr, nullptr, &srcFondInterface.w, &srcFondInterface.h);
    SDL_QueryTexture(_textureRessourcesInterface, nullptr, nullptr, &srcRessourcesInterface.w, &srcRessourcesInterface.h);
    SDL_QueryTexture(_textureFondInterface, nullptr, nullptr, &srcFondInterface2.w, &srcFondInterface2.h);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    dessiner(renderer, _textureRessourcesInterface, srcRessourcesInterface, dstRessourcesInterface);
    dessiner(renderer, _textureFondInterface, srcFondInterface, dstFondInterface);
    dessiner(renderer, _textureFondInterface, srcFondInterface2, dstFondInterface2);

    for (int i = 0; i < 9; i++)
    {
        _tabPays[i]->afficherPays(renderer);
    }

    for (int i = 0; i < 6; i++)
    {
        _tabBouton[i]->afficherBouton(renderer);
    }

    // Affichage valeurs des ressources
    _joueur.afficherJoueur(renderer);

    SDL_RenderPresent(renderer);
}

// Recupere la position de la souris
// et renvoie l'id du pays selectionne
// Renvoie id entre 0 et 8 => pays
// Et renvoie -1 si pas dans la bonne zone

int Manager::ileChoisie(int xMouse, int yMouse)
{
    int tailleCaseIle = 200;
    int id = -1;

    if (xMouse <= 600)
    {
        id = 3 * (yMouse / tailleCaseIle);
        id += xMouse / tailleCaseIle;
    }
    return id;
}

// Crée les alliances entre les pays
// 4 alliances
// Entre 1 et 3 pays par alliance
void Manager::creerAlliance()
{
    int nbPays = 9;
    int nbPaysHorsAlliance = nbPays;
    int nbPaysAlliance;
    vector<Pays *> allianceCour;

    // Dire que tous les pays ne sont pas encore dans une alliance
    bool estAllie[9];
    int indice;
    for (int k = 0; k < nbPays; ++k)
    {
        estAllie[k] = false;
    }

    // Sortir le pays du joueur (par defaut 4)
    estAllie[4] = true; // Pour ne pas etre pris en compte
    nbPaysHorsAlliance--;

    while (nbPaysHorsAlliance > 0)
    {
        allianceCour.clear();              // Reset membre alliance
        nbPaysAlliance = 1 + (rand() % 3); // [|1,3|]
        do                                 // Recuperation des pays d'une alliance
        {
            // Choisir un pays
            indice = rand() % 9;
            if (!estAllie[indice])
            { // Pays aucune alliance => ajoute
                allianceCour.push_back(_tabPays[indice]);
                estAllie[indice] = true;
                nbPaysHorsAlliance--;
            }
        } while (nbPaysHorsAlliance > 0 &&
                 (int)allianceCour.size() <= nbPaysAlliance);

        // Ajout de l'alliance au pays membre
        for (auto p : allianceCour)
        {
            p->setAlliance(allianceCour);
        }
    }
}

void Manager::checkBouton(int xMouse, int yMouse)
{
    for (int k = 0; k < 6; k++)
        _tabBouton[k]->setEtatBouton(_tabBouton[k]->detectionClique(xMouse, yMouse));
}

// Retourne l'etat de isOpen
bool Manager::Partie(int nbTour, SDL_Renderer *renderer)
{
    // Init la partie avec le joueur et les alliances
    // Et les textures
    initJeu(renderer);

    int idIleChoisie = -1;
    int nbTourEcoule = 0;

    SDL_Event events;
    bool isOpen{true};
    bool partieEnCours = true;

    while (isOpen && partieEnCours)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT)
                {
                    // Selectionne ile
                    idIleChoisie = ileChoisie(events.button.x, events.button.y);
                    if (idIleChoisie == -1)
                    {
                        // Selection les btn
                        checkBouton(events.button.x, events.button.y);
                    }
                }
            }

            nbTourEcoule += tour(idIleChoisie);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            afficher(renderer);
        }
    }

    return isOpen;
}

bool Manager::tour(int idIleChoisie)
{
    bool nouveauTour = false;
    if (_joueur.getPtAction() > 0)
    { // Action joueur
        cout << "point action : " << _joueur.getPtAction() << endl;
        if (_tabBouton[btnTransformer]->getEtatBouton())
        { // Bouton active => transfo ressource
            cout << _joueur.transformerRessource() << endl;
            _tabBouton[btnTransformer]->setEtatBouton(false);
        }
        else
        {
            // cout << "pays select :  " << idIleChoisie << endl;
            if (idIleChoisie != -1)
            { // Une ile selectionne
                // Recupere le pays select
                Pays *paysSelect = _tabPays[idIleChoisie];

                if (_tabBouton[btnAccord]->getEtatBouton())
                {
                    cout << _joueur.accordCommercial(*paysSelect) << endl;
                    _tabBouton[btnAccord]->setEtatBouton(false);
                }
                else if (_tabBouton[btnAcheter]->getEtatBouton())
                {
                    cout << _joueur.acheter(*paysSelect) << endl;
                    _tabBouton[btnAcheter]->setEtatBouton(false);
                }
                else if (_tabBouton[btnConvertir]->getEtatBouton())
                {
                    cout << _joueur.convertir(*paysSelect) << endl;
                    _tabBouton[btnConvertir]->setEtatBouton(false);
                }
                else if (_tabBouton[btnGuerreMilitaire]->getEtatBouton())
                {
                    cout << _joueur.attaqueArmee(*paysSelect) << endl;
                    _tabBouton[btnGuerreMilitaire]->setEtatBouton(false);
                }
                else if (_tabBouton[btnGuerreReligueuse]->getEtatBouton())
                {
                    cout << _joueur.attaqueReligion(*paysSelect) << endl;
                    _tabBouton[btnGuerreReligueuse]->setEtatBouton(false);
                }
            }
        }
    }
    else
    { // Nouveau tour
        nouveauTour = true;
        for (auto p : _tabPays)
            p->nouveauTour();

        _joueur.nouveauTour();
    }

    return nouveauTour;
}

// Fonction qui contient le menu pour lancer partie
void Manager::jeu(SDL_Renderer *renderer)
{
    SDL_Event events;
    bool isOpen{true};
    bool isPlay{false};

    SDL_Rect srcFondMenu{0, 0, 0, 0};
    SDL_Rect dstFondMenu{0, 0, 1100, 600};

    SDL_QueryTexture(_textureMenuFond, nullptr, nullptr, &srcFondMenu.w, &srcFondMenu.h);

    while (isOpen)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = false;
                break;
            case SDL_KEYDOWN:
                if (events.key.keysym.sym == SDLK_ESCAPE)
                    isOpen = false;
                else if (events.key.keysym.sym == SDLK_UP)
                {
                    _menu.moveUp();
                }
                else if (events.key.keysym.sym == SDLK_DOWN)
                {
                    _menu.moveDown();
                }
                else if (events.key.keysym.sym == SDLK_RETURN)
                {
                    _menu.select();
                }
                break;
            }
            if (!isPlay)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                dessiner(renderer, _textureMenuFond, srcFondMenu, dstFondMenu);
                _menu.dessinerMenu(renderer);

                SDL_RenderPresent(renderer);

                if (_menu.getIsSelect())
                {
                    _menu.setIsSelectFalse();
                    switch (_menu.getCurrentIndex())
                    {
                    case MENU_JEU:
                        isPlay = true;
                        break;
                    case MENU_CREDIT:
                        break;
                    case MENU_INSTRUCTION:
                        break;
                    case MENU_QUIT:
                        isOpen = false;
                        break;
                    }
                }
            }
            else
            {
                isOpen = Partie(30, renderer);
                isPlay = false;
            }
        }
    }
}
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dessin.hpp"
#include "Pays.hpp"
#include "Joueur.hpp"
#include "Menu.hpp"
#include "Bouton.hpp"
#include "Manager.hpp"


int main(int, char **)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
    }

    if (TTF_Init() < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Menu menu;

    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};

    if (SDL_CreateWindowAndRenderer(1100, 600, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Your (k) Reign");

    Manager manager;
    manager.initJeu(renderer);
    manager.afficher(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    /*
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
    }

    if (TTF_Init() < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    Menu menu;

    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};

    if (SDL_CreateWindowAndRenderer(1100, 600, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Your (k) Reign");

    SDL_Rect src1{0, 0, 0, 0};
    SDL_Rect dst1{980, 0, 120, 600};

    SDL_Surface *imagesMenuRessource;

    imagesMenuRessource = IMG_Load("../img/menu/interface_ressource_verticale.png");


    SDL_Texture *textureMenu = SDL_CreateTextureFromSurface(renderer, imagesMenuRessource);
    SDL_FreeSurface(imagesMenuRessource);

    SDL_QueryTexture(textureMenu, nullptr, nullptr, &src1.w, &src1.h);

    Pays::chargerTexture(renderer);
    Bouton::chargerTexture(renderer);

    Bouton boutonTest(0,false);

    menu.setPosition(250, 140);

    SDL_Color hoverColor = {26, 62, 137, 250};
    SDL_Color normalColor = {150, 150, 150, 250};
    menu.setColor(normalColor, hoverColor);

    menu.chargerTexture(renderer, "Jouer");
    menu.chargerTexture(renderer, "Instructions");
    menu.chargerTexture(renderer, "Credits");
    menu.chargerTexture(renderer, "Quitter");

    Pays pays(0, "Ukraine", 10, RessourceBase::RB0, EtatPays::Neutre);
    Pays pays1(1, "Russie", 15, RessourceBase::RB1, EtatPays::Neutre);
    Pays pays2(2, "Serbie", 5, RessourceBase::RB2, EtatPays::Neutre);
    Pays pays3(3, "Bosnie", 10, RessourceBase::RB3, EtatPays::Neutre);
    Pays pays4(4, "Slovaquie", 100, RessourceBase::RB4, EtatPays::Neutre);
    Pays pays5(5, "Pologne", 15, RessourceBase::RB5, EtatPays::Neutre);
    Pays pays6(6, "Chypre", 20, RessourceBase::RB6, EtatPays::Neutre);
    Pays pays7(7, "Malte", 5, RessourceBase::RB7, EtatPays::Neutre);
    Pays pays8(8, "Corse", 0, RessourceBase::RB8, EtatPays::Neutre);

    SDL_Event events;
    bool isOpen{true};
    bool isPlay{false};
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
                    menu.moveUp();
                }
                else if (events.key.keysym.sym == SDLK_DOWN)
                {
                    menu.moveDown();
                }
                else if (events.key.keysym.sym == SDLK_SPACE)
                {
                    menu.select();
                }
                break;
            }

            if (!isPlay)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                menu.dessinerMenu(renderer);

                SDL_RenderPresent(renderer);

                if (menu.getIsSelect())
                {
                    menu.setIsSelectFalse();
                    switch (menu.getCurrentIndex())
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
            if (isPlay)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                dessiner(renderer, textureMenu, src1, dst1);
                boutonTest.afficherBouton(renderer);
                
                pays.afficherPays(renderer);
                pays1.afficherPays(renderer);
                pays2.afficherPays(renderer);
                pays3.afficherPays(renderer);
                pays4.afficherPays(renderer);
                pays5.afficherPays(renderer);
                pays6.afficherPays(renderer);
                pays7.afficherPays(renderer);
                pays8.afficherPays(renderer);

                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyTexture(textureMenu);
    Bouton::detruireTexture();
    Pays::detruireTexture();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    */
    return EXIT_SUCCESS;
}

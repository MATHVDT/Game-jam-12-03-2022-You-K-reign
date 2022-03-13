#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dessin.hpp"
#include "Pays.hpp"
#include "Bouton.hpp"

int main(int, char **)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
    }

    SDL_Window *window{nullptr};
    SDL_Renderer *renderer{nullptr};

    if (SDL_CreateWindowAndRenderer(980, 600, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Simulation Géopolitique");

    SDL_Rect src1{0, 0, 0, 0};
    SDL_Rect dst1{600, 0, 380, 600};

    SDL_Surface *imagesMenu;
    
    imagesMenu = IMG_Load("../menu.png");

    //SDL_Texture *textureMenu = SDL_CreateTextureFromSurface(renderer, imagesMenu);
    SDL_FreeSurface(imagesMenu);

    //SDL_QueryTexture(textureMenu, nullptr, nullptr, &src1.w, &src1.h);

    Pays::chargerTexture(renderer);
    Bouton::chargerTexture(renderer);

    Bouton boutonTest(0,false);

    Pays paysTest(0,"Ukraine",2,RessourceBase::RB0,EtatPays::Accord);

    SDL_Event events;
    bool isOpen{true};
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
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //dessiner(renderer, textureMenu, src1, dst1);
        paysTest.afficherPays(renderer);
        boutonTest.afficherBouton(renderer);

        SDL_RenderPresent(renderer);
    }
    //SDL_DestroyTexture(textureMenu);
    Bouton::detruireTexture();
    Pays::detruireTexture();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
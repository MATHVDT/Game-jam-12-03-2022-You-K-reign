#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "dessin.hpp"

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

    srand(time(0));

    int ressources[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 9; i++)
    {
        ressources[i] = rand() % 9 + 5;
        printf("%d ", ressources[i]);
    }
    printf("\n");

    int etats[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

    int tab[4] = {90, 180, 270, 0};
    double angle[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 9; i++)
    {
        angle[i] = tab[rand() % 4];
    }

    SDL_SetWindowTitle(window, "Simulation Géopolitique");

    SDL_Surface *images[18];
    images[0] = IMG_Load("../menu.png");
    images[1] = IMG_Load("../img/fond_ile.png");
    images[2] = IMG_Load("../img/en_guerre.png");
    images[3] = IMG_Load("../img/accord_commercial.png");
    images[4] = IMG_Load("../img/conquis.png");
    images[5] = IMG_Load("../img/ressources/ressource_1.png");
    images[6] = IMG_Load("../img/ressources/ressource_2.png");
    images[7] = IMG_Load("../img/ressources/ressource_3.png");
    images[8] = IMG_Load("../img/ressources/ressource_4.png");
    images[9] = IMG_Load("../img/ressources/ressource_5.png");
    images[10] = IMG_Load("../img/ressources/ressource_6.png");
    images[11] = IMG_Load("../img/ressources/ressource_7.png");
    images[12] = IMG_Load("../img/ressources/ressource_8.png");
    images[13] = IMG_Load("../img/ressources/ressource_9.png");
    images[14] = IMG_Load("../img/ressources_craft/ressource__craft_1.png");
    images[15] = IMG_Load("../img/ressources_craft/ressource__craft_2.png");
    images[16] = IMG_Load("../img/ressources_craft/ressource__craft_3.png");
    images[17] = IMG_Load("../img/ressources_craft/ressource__craft_4.png");

    SDL_Texture *textures[18];
    for (int i = 0; i < 18; i++)
    {
        textures[i] = SDL_CreateTextureFromSurface(renderer, images[i]);
    }

    for (int i = 0; i < 18; i++)
    {
        SDL_FreeSurface(images[i]);
    }
    SDL_Rect src1{0, 0, 0, 0};
    SDL_Rect dst1{600, 0, 380, 600};

    SDL_QueryTexture(textures[0], nullptr, nullptr, &src1.w, &src1.h);

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

        dessiner(renderer, textures[0], src1, dst1);
        dessinerIles(renderer, textures[1], angle);
        dessinerEtat(renderer, textures, etats);
        dessinerRessource(renderer, textures, ressources);

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < 18; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
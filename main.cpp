#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    SDL_Surface *image = IMG_Load("fond.png");
    SDL_Surface *image2 = IMG_Load("menu.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, image2);
    SDL_FreeSurface(image);
    SDL_FreeSurface(image2);
    SDL_Rect src1{0, 0, 0, 0};
    SDL_Rect dst1{0, 0, 600, 600};
    SDL_Rect src2{0, 0, 0, 0};
    SDL_Rect dst2{600, 0, 380, 600};

    SDL_QueryTexture(texture, nullptr, nullptr, &src1.w, &src1.h);
    SDL_QueryTexture(texture2, nullptr, nullptr, &src2.w, &src2.h);

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
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, &src1, &dst1);
        SDL_RenderCopy(renderer, texture2, &src2, &dst2);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
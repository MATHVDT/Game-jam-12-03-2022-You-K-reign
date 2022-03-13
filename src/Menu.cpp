#include "Menu.hpp"

Menu::Menu()
{
}

void Menu::chargerTexture(SDL_Renderer *renderer, const char * text)
{
    TTF_Font *font = TTF_OpenFont("arial.ttf", 50);

    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] %s", SDL_GetError());
    }

    menuElement m_el;

    SDL_Surface *surfaceHover = TTF_RenderText_Blended(font, text, m_colorHover);
    SDL_Surface *surfaceNormal = TTF_RenderText_Blended(font, text, m_colorNormal);

    m_el.textureHover = SDL_CreateTextureFromSurface(renderer, surfaceHover);
    m_el.textureNormal = SDL_CreateTextureFromSurface(renderer, surfaceNormal);

    this->m_menuElementList.push_back(m_el);
    this->m_currentIndex = 0;

    SDL_FreeSurface(surfaceHover);
    SDL_FreeSurface(surfaceNormal);

    TTF_CloseFont(font);
}

void Menu::dessinerMenu(SDL_Renderer *renderer)
{
    SDL_Rect src = {0, 0, 0, 0};
    SDL_Rect dst = {0, 0, 200, 50};
    for (int i = 0; i < getMenuSize(); i++)
    {
        dst.x = this->m_posX;
        dst.y = this->m_posY + i * 100 + 10;
        if (this->m_currentIndex == i)
        {

            SDL_QueryTexture(this->m_menuElementList.at(i).textureHover, nullptr, nullptr, &src.w, &src.h);
            SDL_RenderCopy(renderer, this->m_menuElementList.at(i).textureHover, &src, &dst);
        }
        else
        {
            SDL_QueryTexture(this->m_menuElementList.at(i).textureNormal, nullptr, nullptr, &src.w, &src.h);
            SDL_RenderCopy(renderer, this->m_menuElementList.at(i).textureNormal, &src, &dst);
        }
    }
}

void Menu::setColor(SDL_Color colorNormal, SDL_Color colorHover)
{
    this->m_colorNormal = colorNormal;
    this->m_colorHover = colorHover;
}

void Menu::setPosition(int X, int Y)
{
    this->m_posX = X;
    this->m_posY = Y;
}

int Menu::getCurrentIndex()
{
    return this->m_currentIndex;
}

int Menu::getMenuSize()
{
    return this->m_menuElementList.size();
}

bool Menu::getIsSelect()
{
    return this->m_select;
}

void Menu::setIsSelectFalse()
{
    this->m_select = false;
}

void Menu::moveUp()
{
    if (getCurrentIndex())
    {
        m_currentIndex--;
    }
}

void Menu::moveDown()
{
    if (getCurrentIndex() != (getMenuSize() - 1))
    {
        m_currentIndex++;
    }
}

void Menu::select()
{
    m_select = true;
}

Menu::~Menu()
{
}
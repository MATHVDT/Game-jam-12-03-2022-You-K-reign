#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct menuElement
{
    SDL_Texture *textureNormal;
    SDL_Texture *textureHover;
};

enum MENU_LINK {
MENU_JEU,
MENU_INSTRUCTION,
MENU_CREDIT,
MENU_QUIT
};

class Menu
{
private:
    int m_currentIndex;
    bool m_select = false;
    int m_posX;
    int m_posY;
    SDL_Color m_colorHover;
    SDL_Color m_colorNormal;
    std::vector<menuElement> m_menuElementList;

public:
    Menu();
    void chargerTexture(SDL_Renderer * renderer, const char * text);
    void dessinerMenu(SDL_Renderer * renderer);
    void setPosition(int X, int Y);
    void setColor(SDL_Color colorNormal, SDL_Color colorHover);
    int getCurrentIndex();
    int getMenuSize();
    bool getIsSelect();
    void setIsSelectFalse();
    void moveUp();
    void moveDown();
    void select();
    virtual ~Menu();
};

#endif
#include "dessin.hpp"

using namespace std;

class Bouton
{
    private:
        int _idBouton;
        bool _etatBouton;
        SDL_Rect _position;
        SDL_Texture *_textureBoutonId[2];

    public:
        static SDL_Texture *_textureBoutons[12];

    public:
        void static chargerTexture(SDL_Renderer *);
        void chargerTextureBouton(SDL_Texture *[], int);
        void chargerPosition(int idBouton, int x, int y, int w, int h);
        bool detectionClique(int xSouris, int ySouris);
        void afficherBouton(SDL_Renderer *);
};
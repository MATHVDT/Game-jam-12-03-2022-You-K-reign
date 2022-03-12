#include "dessin.hpp"
#include <iostream>

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
        Bouton(int idBouton, bool etatBouton);
        ~Bouton() = default;
        void static chargerTexture(SDL_Renderer *);
        void chargerBouton(SDL_Texture *[]);

        bool detectionClique(int xSouris, int ySouris);
        void afficherBouton(SDL_Renderer *);

        void detruireTextureBouton();
        void static detruireTexture();
};
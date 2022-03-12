#include <iostream>

#include "Pays.hpp"

using namespace std;

int main(int, char **)
{

    cout << "Hello world !" << endl;

    Pays p{0, "france", 1, RessourceBase::RB0};
    p.nouveauTour();
    p.afficherConsole();
    p.accordCommercial();
    p.annexer();
    p.nouveauTour();
    p.nouveauTour();
    p.nouveauTour();
    p.afficherConsole();
    return 0;
}

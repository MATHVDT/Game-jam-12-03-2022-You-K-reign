#include <iostream>

// #include "Pays.hpp"
#include "Joueur.hpp"

using namespace std;

int main(int, char **)
{

    cout << "Hello world !" << endl;

    Pays *p = new Pays{5, "France", 100, RessourceBase::RB0};
    Pays *p2 = new Pays{1, "Pologne", 5, RessourceBase::RB2};

    Joueur j{p};
    p2->nouveauTour();
    j.nouveauTour();
    j.setStockRBi(0, 5);
    j.setStockRBi(2, 2);
    j.setStockRCi(2, 5);
    j.setStockRCi(1, 8);

    for (int i = 0; i < 9; i++)
        cout << j.getStockRBi(i) << " ";

    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << j.getStockRCi(i) << " ";
    cout << endl;

    cout << endl
         << "pt : " << j.getPtAction() << "  RB dispo : " << p2->getRessourceDispo() << endl;

    /**************** DEBUT ACTION ******************/
    // cout << j.acheter(*p2);

    cout << j.convertir(*p2) << endl;
    cout << j.convertir(*p2) << endl;
    cout << j.convertir(*p2) << endl;
    cout << j.attaqueReligion(*p2) << endl;

    /***************** FIN ACTION ******************/

    cout << endl
         << "pt : " << j.getPtAction() << "  RB dispo : " << p2->getRessourceDispo() << endl;

    cout << "achat" << endl;
    for (int i = 0; i < 9; i++)
        cout << j.getStockRBi(i) << " ";

    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << j.getStockRCi(i) << " ";
    cout << endl;

    cout << j.getPaysOrigin()->getId();

    delete p;

    return 0;
}

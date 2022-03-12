#include <iostream>

// #include "Pays.hpp"
#include "Joueur.hpp"

using namespace std;

int main(int, char **)
{

    cout << "Hello world !" << endl;

    Pays *p = new Pays{0, "France", 100, RessourceBase::RB0};
    Pays *p2 = new Pays{1, "Pologne", 5, RessourceBase::RB2};

    Joueur j{p};
    p2->nouveauTour();
    j.annexerPays(*p2);
    j.nouveauTour();

    for (int i = 0; i < 9; i++)
        cout << j.getStockRBi(i) << " ";

    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << j.getStockRCi(i) << " ";
    cout << endl;

    cout << endl
         << "pt : " << j.getPtAction() << "  RB dispo : " << p2->getRessourceDispo() << endl;
    // cout << j.acheter(*p2);
    cout << endl
         << "pt : " << j.getPtAction() << "  RB dispo : " << p2->getRessourceDispo() << endl;

    cout << "achat" << endl;
    for (int i = 0; i < 9; i++)
        cout << j.getStockRBi(i) << " ";

    cout << endl;
    for (int i = 0; i < 3; i++)
        cout << j.getStockRCi(i) << " ";
    cout << endl;

    delete p;

    return 0;
}

#include "Creation.cpp"
using namespace std;
#include <bits/stdc++.h>

int main(int argc, char* argv[])
{
    srand((unsigned) time(NULL));
    /*cout << "Ceci est un menu. Choisissez ce que vous voulez faire: 0: demarrer une nouvelle partie"<< endl;
    bool depart = false;
    while(!depart)
    {
        int choix; cin >> choix;
        switch(choix)
        {
            case 0: 
            lire("Introduction");
            lire("Creation_perso");
            depart = true;
            break;
        }        

    }*/
    Inventaire inv = Inventaire(16);
    Inventaire inv2 = Inventaire(11);

    int tab[5] = {10,15,16,17,11};
    int tab2[5] = {20,17,11,14,20};

    Personnage p = Personnage("k",16,"orc",tab,inv);
    Personnage p2 = Personnage("l", 19,"humain", tab2, inv2);
    //cout << p.getInventaire().getPoidsMax();
    Arme a = Arme("Fleau de Dieu", 10,400,"Fer Celeste");
    Arme a2 = Arme("Lance d'Odin", 100,300,"Cuivre Celeste");

    p.recupererObjet(a);
    Armure am = Armure();   
    p.recupererObjet(am);
    p2.recupererObjet(a2);
    p2.recupererObjet(am);
    vector<Personnage> vec;
    vec.push_back(p); vec.push_back(p2);
    int i =0;
    LancerCombat(vec);

return 0;
} 
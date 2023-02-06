#include "Creation.cpp"
using namespace std;

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
    int tab[5] = {10,15,16,17,11};
    Personnage p = Personnage("k",16,"orc",tab,inv);
    //cout << p.getInventaire().getPoidsMax();
    Arme a = Arme("Fleau de Dieu", 10,400,"Fer Celeste");
    p.recupererObjet(a);
    Armure am = Armure();
    p.recupererObjet(am);
    p.getInventaire().afficherInventaire();

return 0;
} 
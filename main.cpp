#include "Creation.cpp"
using namespace std;

int main(int argc, char* argv[])
{
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
    Personnage p1 =ChargerPerso("j");
    p1.getStats().AfficheStats();

return 0;
} 
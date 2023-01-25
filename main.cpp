#include "Creation.cpp"
using namespace std;


int main(int argc, char* argv[])
{
    cout << "Ceci est un menu. Choisissez ce que vous voulez faire: 0: demarrer une nouvelle partie"<< endl;
    bool depart = false;
    while(!depart)
    {
        int choix; cin >> choix;
        switch(choix)
        {
            case 0: 
            /*lire("Introduction");
            lire("Creation_perso");*/
            string word;
            cin >> word;
            ChargerPerso(word);
            depart = true;
            break;
        }        

    }
    
return 0;
} 
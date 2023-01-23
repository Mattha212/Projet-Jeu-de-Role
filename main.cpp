#include "Creation.cpp"
using namespace std;


int main(int argc, char* argv[])
{
    cout << "Ceci est un menu. Choisissez ce que vous voulez faire."<< endl;
    bool depart = false;
    while(!depart)
    {
        int choix; cin >> choix;
        switch(choix)
        {
            case 0: 
            lire("Introduction");
            lire("Creation_perso");
            Personnage pj = Personnage();
            pj.afficheStats();
            break;
        }        
    }
    
return 0;
} 
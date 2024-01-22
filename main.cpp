#include "Personnage.hpp"
using namespace std;

bool LePlusRapide(Personnage p1, Personnage p2){
    return p1.getStats().getStatfromString("VIT")>p2.getStats().getStatfromString("VIT");
}
bool PersoMort(Personnage p)
{
    if(p.getVie()<=0) return true;
    else return false;
}

Personnage ChargerPerso(string nom)
{
    ifstream MyExcelFile ;
    MyExcelFile.open("..\\test.csv", fstream::app); 
    string line, word; int i =1;string  race; int age=0; int stat[5];int vie =0;
    bool test = false;
    while(getline(MyExcelFile, line)  && !test)
    {
    stringstream str(line), ss;
    getline(str, word, ';');
    if(word==nom)
    {
        while(getline(str, word, ';') && i<9)
        {
            switch(i)
            {
                case 1:age = stoi(word);
                break;
                case 2:race = word;
                break;
                case 3:stat[0]=stoi(word);break;
                case 4:stat[1]=stoi(word);break;
                case 5:stat[2]=stoi(word);break;
                case 6:stat[3]=stoi(word);break;
                case 7:stat[4]=stoi(word);break;
                case 8:vie = stoi(word); test=true; break;
            }         
            i++;
        }
    }
    }
    Inventaire inv  = Inventaire(stat[2]);
    Personnage p = Personnage(nom,age,race,stat,inv);
    if(p.getVie()!=vie)p.setVie(vie);
    return p;
}
void RoundDeCombat(vector<Personnage> &pjs){
    cout << "debut du tour" << endl;
    cout << pjs[0].getNom() + ": " << pjs.at(0).getVie() << " PVs" << " " << pjs[1].getNom() + ": " << pjs.at(1).getVie() << " PVs" << endl;
    sort(pjs.begin(), pjs.end(), LePlusRapide);
    for(auto &it :pjs){
        if(!(pjs.at(0).IsAlive() * pjs.at(1).IsAlive())) {
            if(!pjs.at(0).IsAlive() && pjs.at(1).IsAlive()){
                cout << pjs.at(0).getNom() << " est mort!" << endl;
                break;
            }
            else if(!pjs.at(1).IsAlive() && pjs.at(0).IsAlive()){
                cout << pjs.at(1).getNom() << " est mort!" << endl;
                break;
            }
            else{
                cout << pjs.at(0).getNom() <<" et " << pjs.at(1).getNom() << " sont mort!" << endl;
                break;
            }
        }
        cout << "c'est le tour de " << it.getNom() << ", que va-t-il faire?" << endl;
        cout << "1: se soigner, 2: attaquer quelqu'un" << endl;
        int action;
        cin >> action ;
        switch(action){
            case 1:
            //utiliser un sort de soin (faut gérer la mana et les sorts)
                cout << "la feature sera bientot disponible" << endl;
                break;
            case 2:{
            for_each(pjs.begin(), pjs.end(), [&, i = 0](auto& it1) mutable {
                cout << i << ": " << (it1).getNom() << " "; i++;
                });
                 cout << endl;
            cout << "qui attaquer? Donnez le numero du personnage" << endl;
            int cible;
            cin >> cible;
            it.Attaquer(pjs.at(cible));
            break;
            }
            default:
            cout << "ce n'est pas un choix encore possible!" << endl;
            break;
        }
    }
    cout << "fin du tour" << endl;
    cout << pjs[0].getNom() + ": " << pjs.at(0).getVie() << " " << pjs[1].getNom() + ": " << pjs.at(1).getVie() << endl;


    //return pjs;
};



int main(int argc, char* argv[])
{
    srand((unsigned) time(NULL));
   Personnage p1 = ChargerPerso("Jugad");
   Personnage p = Personnage();
   cout << p.getNom() << endl;
    return 0;
} 
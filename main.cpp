#include "Personnage.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <stdlib.h>
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
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app); 
    string line, word; int i =1;string  race; int age; int stat[5];int vie =0;
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
    sort(pjs.begin(), pjs.end(), LePlusRapide);
    cout << pjs.at(0).getVie() << " " << pjs.at(1).getVie() << endl;
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
            else if(!pjs.at(0).IsAlive() && !pjs.at(1).IsAlive()){
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
            case 2:{
            int i =0;
            for(vector<Personnage>::iterator it1=pjs.begin(); it1 !=pjs.end();it1++ ){
                 cout << i << ": " << (*it1).getNom() << " " ; i++;}
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
    //return pjs;
};


int main(int argc, char* argv[])
{
    srand((unsigned) time(NULL));
    Personnage p1 = ChargerPerso("Jugad"); Personnage p2 = ChargerPerso("victime");
    vector<Personnage> ps= {p1,p2};

    while(ps.at(0).IsAlive() && ps.at(1).IsAlive()){
    cout << ps.at(0).getVie() << " " << ps.at(1).getVie() << endl;
    RoundDeCombat(ps);
    cout << "fin du tour" << endl;
    /*Personnage p1 = ps.at(0), p2 = ps.at(1);
    ps = {p1, p2};*/
    cout << ps.at(0).getVie() << " " << ps.at(1).getVie() << endl;
    
    }
    /*while(p2.IsAlive()){
    p1.Attaquer(p2);
    }*/
    return 0;
} 
#include "Personnage.hpp"
using namespace std;


void lire(string s)
{
    string s1 = s + ".txt";
    fstream flux(s1, ios::in);
    if(flux)
    {
        string ligne;
        while(getline(flux, ligne))  
        {
                cout << ligne << endl; 
        }
        flux.close();
    }
}


void Personnage::CreerPersonnage()
{
    m_stats = Stats();
    fflush(stdin);
    
    string nom; int age; string race;int bouton;int compteur =0;
    m_inventaire = new Inventaire();
    cout << "Qui etes vous?" << endl;
    cout << "Votre nom: "<< endl;
    getline(cin,nom) ;
    fflush(stdin);
    m_nom=nom;
    cout << "1 : Precisions sur les humains 2 : Precisions sur les elfes 3: Precisions sur les orcs 0 : Entrer votre race" << endl;
    
    vector<string> tab = {"elfe", "orc","humain"};
    while(race.empty())
    {
        cin >> bouton;
        switch(bouton)
        {
            case 1:
            lire("Race_Humain");
            break;
            case 2:
            lire("Race_Elfe");
            break;
            case 3:
            lire("Race_Orc");
            break;
            case 0:
            cout << "Votre race:"<< endl;
            do{
            cin >> race;
            auto breakthecasseLow = [](char& lettre) {
                return tolower(lettre);
                };
            transform(race.begin(), race.end(), race.begin(), breakthecasseLow);
            if (count(tab.begin(), tab.end(), race) >= 1) break;
            cout << "Ce n'est pas une race disponible!" << endl;

            } while(true);
            break;
            default:
            cout << "Ce n est pas un choix possible"<< endl;
        }
        
        compteur++;
    }
    fflush(stdin);
    int valeur0 = rand()%20+1;int valeur1 = rand()%20+1;
    int valeur2 = rand()%20+1;int valeur3 = rand()%20+1;int valeur4 = rand()%20+1;
    map<int, int> v;
    v[valeur0] ++;v[valeur1] ++;v[valeur2] ++;v[valeur3] ++;v[valeur4] ++;
    m_race=race;
    while(true)
    {    
        map<int, int>::iterator it = v.begin();
        while(it!= v.end())
        {
            cout << it->first << "(" << it->second << ") ";
            it++;
        }
        cout << endl;
        m_stats.AfficheStats();
        string statistique;
        while (true) {
            cout << "A quelle statistique voulez vous attribuer une valeur?" << endl;
            cin >> statistique;
            auto breakthecasseSup = [](char& lettre) {
                return toupper(lettre);
                };
            transform(statistique.begin(), statistique.end(), statistique.begin(), breakthecasseSup);
            if (m_stats.CountFelement(statistique) != 0) break;
            cout << "ce n'est pas une stat valide!" << endl;
        }

        int valeur;
        while(!(cin>> valeur) || valeur > 20 || v[valeur]==0)
        {
            cout << "Quelle valeur voulez vous donner a la statistique " + statistique + " ?" << endl;
            v.erase(valeur);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ce n'est pas une valeur disponible!" << endl;
        }

        if(m_stats.CountFelement(statistique)>0)
        {
            
            if(m_stats.getStatfromString(statistique)>0)
            {
                v[m_stats.getStatfromString(statistique)]++;
                m_stats.SetStat(statistique, valeur);
                v[valeur]--;
            }
            else{
                m_stats.SetStat(statistique, valeur);
                switch(v[valeur])
                {
                    case 0:
                    v.erase(valeur);
                    default:
                    v[valeur]--;
                }
        }}
        if(v[valeur0] +v[valeur1] +v[valeur2] + v[valeur3] +v[valeur4]<=0)break;
    }
    ModifRace(m_race);
    m_stats.AfficheStats();
    //construire un menu pour déterminer quelle valeur va dans quel stat, peut être une fonction d'affichage de stat?
    
    
    cout << "Votre age:"<< endl;
    cin >> age;
    fflush(stdin);
    m_age=age;
    m_inventaire->setPoidsMax((m_stats.getStatfromString("CON"))*15);
    m_vie = (m_stats.getStatfromString("CON"))*50;
    
}
Personnage::Personnage()
{
    CreerPersonnage();
    Sauvegarde();
}
Personnage::Personnage(string name, int age, string race, int *stats, Inventaire stuff){
    m_nom= name; m_age = age; m_race = race;  m_stats= Stats(stats, 5); 
        m_inventaire = new Inventaire(m_stats.getStatfromString("CON"));
    if(stuff.getPoidsTotal()>0)
    {
    map<string, Objet>::iterator it = stuff.getMap().begin();
    while(it!=stuff.getMap().end())
    {
        m_inventaire->addObjet(it->second);
    }}
}
Personnage::Personnage(Personnage const& PersoACopier)
{
        m_stats = PersoACopier.m_stats;
        m_nom = PersoACopier.m_nom;
        m_age = PersoACopier.m_age;
        m_race = PersoACopier.m_race;
        m_vie = PersoACopier.m_vie;
        m_inventaire = new Inventaire(m_stats.getStatfromString("CON"));
        if(PersoACopier.m_inventaire->getPoidsTotal()>0)
        {
        map<string, Objet>::iterator it = PersoACopier.m_inventaire->getMap().begin();
        while(it!=PersoACopier.m_inventaire->getMap().end())
        {
            m_inventaire->addObjet(it->second);
            it++;
        }}
        
        
}

bool Personnage::IsAlive(){
    if(getVie()>0)return true;
    else return false;
}
Stats Personnage::getStats()
{
    return m_stats;
}
int Personnage::getVie()
{
    return m_vie;
}
int Personnage::getAge()
{
    return m_age;
}
string Personnage::getNom()
{
    return m_nom;
}
string Personnage::getRace()
{
    return m_race;
}
void Personnage::ModifRace(string race)
{
    
        if(race == "elfe")
        {
            m_stats.SetStat("CON",m_stats.getStatfromString("CON")+1); //CON
            m_stats.SetStat("VIT",m_stats.getStatfromString("VIT")+3); //VIT
            m_stats.SetStat("INT",m_stats.getStatfromString("INT")-1); //INT
        }
        else if(race == "orc") 
        {
            m_stats.SetStat("CHA",m_stats.getStatfromString("CHA")-5); //CHA
            m_stats.SetStat("CON",m_stats.getStatfromString("CON")+2); //CON
            m_stats.SetStat("AGI",m_stats.getStatfromString("AGI")+2); //AGI
            m_stats.SetStat("VIT",m_stats.getStatfromString("VIT")+2); //VIT

        }
        else if(race == "humain") 
        {
            m_stats.SetStat("AGI",m_stats.getStatfromString("AGI")+2); //AGI
            m_stats.SetStat("CHA",m_stats.getStatfromString("CHA")+2); //CHA
            m_stats.SetStat("CON",m_stats.getStatfromString("CON")-1); //CON
        }
    
}
void Personnage::recupererObjet(Objet obj)
{
    m_inventaire->addObjet(obj);
}
void Personnage::jeterObjet(Objet obj)
{
    m_inventaire->throwObjet(obj.getNom());
}
void Personnage::Attaquer(Personnage &cible)
{
     int valeur0 = rand()%20+1; int valeur1 = rand()%20+1;
     if(getStats().getStatfromString("AGI")-valeur0>cible.getStats().getStatfromString("AGI")-valeur1)
     {
        cout << getNom() << " attaque violemment " << cible.getNom() << " !" << endl;
        cible.PrendreDegats(100);
     }
     else cout << getNom() << " rate magnifiquement " << cible.getNom() << "..." << endl;
}
void Personnage::PrendreDegats(int degats)
{
    setVie(getVie()-degats);
    cout << "Il reste a " << getNom() << " " <<getVie()<< " pvs" << endl;
}

void Personnage::setVie(int v)
{
    m_vie= v;
}
void Personnage::Sauvegarde(){
    ofstream MyExcelFile ;
    MyExcelFile.open("..\\test.csv", fstream::app);
    MyExcelFile << "\n";
    MyExcelFile << getNom() + ";" ;
    MyExcelFile << getAge() << " ans;";
    MyExcelFile << getRace() + ";";
    fflush(stdin);  
    auto v = m_stats.getStat();
    for_each(v.begin(), v.end(), [&](auto& it) mutable {
        MyExcelFile << it.second  << ";";
        });

    MyExcelFile << getVie() << ";";
    MyExcelFile << "\n";

    MyExcelFile.close();
};
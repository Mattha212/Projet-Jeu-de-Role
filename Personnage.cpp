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

int PairCountFelement(Stats v,string a)
{
    int nb =0;
    for(int i=0;i<v.getSize();i++)
    {   
        if(v.getChar(i)==a)nb++; 
    }
    return nb;
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
    const string s =  "1 : Precisions sur les humains 2 : Precisions sur les elfes 3: Precisions sur les orcs 0 : Entrer votre race";
    
    vector<string> tab = {"elfe", "orc","humain"};
    while(race.empty())
    {
        if(compteur%2==0 || compteur ==0)cout<<s<<endl;
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
            cin >> race;

            for(int i=0; i<(int)race.size();i++)
            {
                 if(race[i]<=90) race[i]+=32;
            }

            while(count(tab.begin(),tab.end(),race)<1)
            {
                cout << "Ce n'est pas une race disponible!" << endl;
                cin >> race;
                for(int i=0; i<(int)race.size();i++)
                {
                    if(race[i]<=90) race[i]+=32;
                }

            }
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
    bool test1 =false; 
    while(!test1)
    {    
        map<int, int>::iterator it = v.begin();
        while(it!= v.end())
        {
            cout << it->first << "(" << it->second << ") ";
            it++;
        }
        cout << endl;
        m_stats.AfficheStats();
        cout << "A quelle statistique voulez vous attribuer une valeur?"<< endl;
        string a;
        cin >> a;
        for(int i=0; i<(int)a.size();i++)
        {
            if(a[i]>=97) a[i]-=32;
        }
       
       while(PairCountFelement(m_stats,a)==0)
        {
            cout << "ce n'est pas une stat valide!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "A quelle statistique voulez vous attribuer une valeur?"<< endl;
            cin >> a;
            for(int i=0; i<(int)a.size();i++)
            {
                if(a[i]>=97) a[i]-=32;
            }
        }
        
        cout << "Quelle valeur voulez vous donner a cette statistique?"<< endl;
        int b;
        while(!(cin>>b) || b > 20 || v[b]==0)
        {
            v.erase(b);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ce n'est pas une valeur disponible!" << endl;
            cout << "Quelle valeur voulez vous donner a la statistique " + a + " ?"<< endl;
        }
        if(PairCountFelement(m_stats,a)>0) 
        {
            
            if(m_stats.getStatfromString(a)>0)
            {
                v[m_stats.getStatfromString(a)]++;
                m_stats.SetStat(a,b);
                v[b]--;
            }
            else{
                m_stats.SetStat(a,b);
                switch(v[b])
                {
                    case 0:
                    v.erase(b);
                    default:
                    v[b]--;
                }
        }}
        if(v[valeur0] +v[valeur1] +v[valeur2] + v[valeur3] +v[valeur4]<=0)test1=true;
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
        cout << this->getNom() << " attaque violemment " << cible.getNom() << " !" << endl;
        cible.PrendreDegats(100);
     }
     else cout << this->getNom() << " rate magnifiquement " << cible.getNom() << "..." << endl;
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
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app);
    MyExcelFile << "\n";
    MyExcelFile << this->getNom() + ";" ;
    MyExcelFile << this->getAge() << " ans;";
    MyExcelFile << this->getRace() + ";";
    fflush(stdin);

    for(int it=0;it<5;it++)
    {
    MyExcelFile << this->getStats().getStatfromIndex(it) <<";";
    } 
    MyExcelFile << this->getVie() << ";";
    MyExcelFile << "\n";

    MyExcelFile.close();
};
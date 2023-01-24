#include "Personnage.hpp"
using namespace std;

void lire(string s)
{
    string s1 = s + ".txt";
    ifstream flux(s1, ios::in);
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

void SavePerso(Personnage p)
{
    ofstream MyExcelFile ;
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app);
    MyExcelFile << "\n";
    MyExcelFile << p.getNom() + ";" ;
    MyExcelFile << p.getAge() << " ans;";
    MyExcelFile << p.getRace() + ";";
    fflush(stdin);
     map<string, int>::iterator it = p.m_stats.begin();

    while(it != p.m_stats.end())
    {
    MyExcelFile << it->first << ": " << p.ValeurStat(it->first) << ";";
    it++;
    } 
    MyExcelFile << p.getVie() << ";";
    MyExcelFile << "\n";

    MyExcelFile.close();
}

Personnage ChargerPerso(string nom)
{
    Personnage p = Personnage();
    ifstream MyExcelFile ;
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app); 
    
}
/**
 * It creates a character and saves it in a csv file.
 */
void Personnage::CreerPersonnage()
{
    fflush(stdin);
    srand((unsigned) time(NULL));
    Inventaire inv = Inventaire();
    string nom; int age; string race;int bouton;int compteur =0;
    m_inventaire = inv;
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
    m_stats["AGI"]=m_stats["INT"]=m_stats["VIT"]=m_stats["CHA"]=m_stats["CON"]=-1;
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
        afficheStats();
        cout << "A quelle statistique voulez vous attribuer une valeur?"<< endl;
        string a;
        cin >> a;
        for(int i=0; i<(int)a.size();i++)
        {
            if(a[i]>=97) a[i]-=32;
        }
       
       while(m_stats[a]==0)
        {
            cout << "ce n'est pas une stat valide!" << endl;
            m_stats.erase(a);
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
        if(m_stats[a]) 
        {
            if(m_stats[a]>0)
            {
                v[m_stats[a]]++;
                m_stats[a] = b;
                v[b]--;
            }
            else{
                m_stats[a]=b;
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
    afficheStats();
    //construire un menu pour déterminer quelle valeur va dans quel stat, peut être une fonction d'affichage de stat?
    
    
    cout << "Votre age:"<< endl;
    cin >> age;
    fflush(stdin);
    m_age=age;
    
    m_inventaire.setPoidsMax(m_stats["CON"]*15);
    
    m_vie = m_stats["CON"]*50;
}

Personnage::Personnage()
{
    m_nom= "rien";
    m_age= 0;
    m_race = "rien";
}
Personnage::Personnage(std::string nom, int age ,std::string race, std::map<std::string, int> stats, Inventaire stuff)
{
        m_nom = nom;
        m_age = age;
        m_race = race;
        m_vie = stats["CON"]*50;
        m_stats["AGI"]=stats["AGI"]; m_stats["CON"]=stats["CON"]; m_stats["INT"]=stats["INT"]; m_stats["VIT"]=stats["VIT"]; m_stats["CHA"]=stats["CHA"];
        map<string, Objet>::iterator it = stuff.getMap().begin();
        while(it!=stuff.getMap().end())
        {
            m_inventaire.addObjet(it->second);
        }
}
map<string, int> Personnage::getStats()
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
/**
 * It takes an integer as an argument, checks if it's between 0 and 4, and if it is, returns the value
 * of the corresponding stat
 * 
 * @param stat the stat you want to get the value of
 * 
 * @return The value of the stat.
 */
void Personnage::ModifRace(string race)
{
    
        if(race == "elfe")
        {
            m_stats["CON"] ++;
            m_stats["VIT"] +=3 ;
            m_stats["INT"] --;
        }
        else if(race == "orc") 
        {
            m_stats["CHA"] -=5;
            m_stats["CON"] +=2;
            m_stats["AGI"] +=2;
            m_stats["VIT"] +=2;

        }
        else if(race == "humain") 
        {
            m_stats["AGI"] +=2;
            m_stats["CHA"] +=2;
            m_stats["CON"] -=2;
        }
    
}

int Personnage::ValeurStat(string stat)
{
    int i = m_stats[stat];
    return i;
} 

void Personnage::afficheStats()
{
 map<string, int>::iterator it = m_stats.begin();

 while(it != m_stats.end())
 {
    cout << it->first << ": " << ValeurStat(it->first) << ";";
    it++;
 }   
cout << "\n";
}
void Personnage::recupererObjet(Objet obj)
{
    m_inventaire.addObjet(obj);
}
void Personnage::jeterObjet(Objet obj)
{
    m_inventaire.throwObjet(obj.getNom());
}
Inventaire Personnage::getInventaire()
{
    return m_inventaire;
}


Inventaire::Inventaire()
{
map <string, Objet> m_inventaire;
m_poidsmax = 0;
m_poidsTotal=0;
}
Objet Inventaire::getObjet(string nom)
{
    return m_inventaire[nom];
}
void Inventaire::addObjet(Objet obj)    
{
    if(m_poidsTotal+obj.getPoids()<= m_poidsmax)
    {
        if(deja_present(obj))
        {
            Objet ob = getObjet(obj.getNom());
            int nbel = ob.getNbElement();
            ob.setNbElement(nbel+1);
            m_inventaire.erase(ob.getNom());
            m_inventaire.insert(make_pair(ob.getNom(),ob));
        }
        else
        {
            m_inventaire.insert(make_pair(obj.getNom(), obj));
        }
        m_poidsTotal+= obj.getPoids();
    }
    else cout << "Votre inventaire est plein! Vous devez jeter des objets avant de pouvoir en prendre a nouveau"<< endl;
}
map<string, Objet> Inventaire::getMap()
{
    return m_inventaire;
}
void Inventaire::throwObjet(string nom)
{
    Objet ob = getObjet(nom);
    int nbel = ob.getNbElement();
    if(nbel>1)
    {
        ob.setNbElement(nbel -1);
        m_inventaire.erase(nom);
        m_inventaire.insert(make_pair(ob.getNom(),ob));
    }
    else m_inventaire.erase(nom);

    m_poidsTotal-= ob.getPoids(); 
}
void Inventaire::afficherInventaire()
{
    map<std::string, Objet>::iterator it;
    for(it= m_inventaire.begin(); it != m_inventaire.end();++it)
    {
        if(getObjet(it->first).getNbElement()>1){
        cout <<  getObjet(it->first).getNom() + "(" << getObjet(it->first).getNbElement()<< ") (" <<"poids: " << getObjet(it->first).getPoids()<< ")" << endl;
    }
    else cout <<  getObjet(it->first).getNom() + " (" <<"poids: " << getObjet(it->first).getPoids() << ")" <<endl;
    }
    cout << "poids total: "<< m_poidsTotal << endl;
    cout << "poids restant: " << m_poidsmax-m_poidsTotal << endl;
    }
void Inventaire::setPoidsMax(int poids) 
{
    m_poidsmax=poids;
}
int Inventaire::getPoidsMax()
{
    return m_poidsmax;
}
bool Inventaire::deja_present(Objet obj)
{
       map<string, Objet>::iterator it = m_inventaire.find(obj.getNom());
       if(it!=m_inventaire.cend()) return true;
       else return false;
       
       
}


Objet::Objet()
{
    m_poids = 1;
    m_nom= "dechet";
    m_nb_element = 1;
}

Objet::Objet(int poids, string nom) 
{
    m_poids = poids;
    m_nom = nom;
    m_nb_element = 1;
}
int Objet::getPoids()
{
    return m_poids;
}
int Objet::getNbElement()
{
    return m_nb_element;
}
string Objet::getNom()
{
    return m_nom;
}
void Objet::setNom(string newnom)
{
    m_nom = newnom;
}
void Objet::setPoids(int newpoids)
{
    m_poids= newpoids;
}
void Objet::setNbElement(int newNbElement)
{
    int p = getPoids()/m_nb_element;
    m_nb_element = newNbElement;
    setPoids(p*newNbElement);
}
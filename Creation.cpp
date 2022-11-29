#include "Creation.hpp"
#include "Setup.hpp"
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
Setup::Setup()
{

    lire("Introduction");
    lire("Creation_perso");
    Personnage pj = Personnage();
}

/**
 * It creates a character and saves it in a csv file.
 */
Personnage::Personnage()
{
    srand((unsigned) time(NULL));
    Inventaire inv = Inventaire();
    string nom; int age; string race;
    m_inventaire = inv;
    cout << "Qui etes vous?" << endl;
    cout << "Votre nom: "<< endl;
    getline(cin,nom) ;
    fflush(stdin);
    m_nom=nom;
    int bouton;
    string s =  "1 : Precisions sur les humains 2 : Precisions sur les elfes 3: Precisions sur les orcs 0 : Entrer votre race";
    cout << s << endl;
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
            cin >> race;
        }
    }
    fflush(stdin);
    m_race=race;
    
    std::map<std::string, int> stats = {{"INT",0},{"AGI",0},{"VIT",0},{"CHA",0},{"CON",0}};
    
    
    int valeur0 = rand()%20+1;int valeur1 = rand()%20+1;int valeur2 = rand()%20+1;int valeur3 = rand()%20+1;int valeur4 = rand()%20+1;
    stats["INT"] = valeur0;stats["AGI"] = valeur1;stats["VIT"] = valeur2;stats["CHA"] = valeur3;stats["CON"] = valeur4;
    //construire un menu pour déterminer quelle valeur va dans quel stat, peut être une fonction d'affichage de stat?
    
    ModifRace(stats, m_race);
    cout << "Votre age:"<< endl;
    cin >> age;
    fflush(stdin);
    m_age=age;
    m_inventaire.setPoidsMax(stats["CON"]*15);
    m_stats = stats;
    m_vie = stats["CON"]*50;
    ofstream MyExcelFile;
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app);
    MyExcelFile << "\n" + getNom() + ";" ;
    MyExcelFile << getAge() << " ans;";
    MyExcelFile <<  getRace() + ";";
    map<string, int>::iterator j = stats.begin();
    while(j!=stats.end())
    {
        MyExcelFile << j->second << ";" ;
        fflush(stdin);
        j++;
    }
    MyExcelFile << m_vie << ";";
    MyExcelFile << "\n";
    MyExcelFile.close();

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
void Personnage::ModifRace(map<string, int> stats, string race)
{
    if(race == "elfe")
    {
        stats["CON"] += 1;
        stats["VIT"] +=3 ;
        stats["INT"] -=1;
        cout<< "elfe" << endl;
    }
    else if(race == "orc") cout << "orc" << endl;
    else if(race == "humain") cout << "humain"<<endl;
}
int Personnage::ValeurStat(string stat)
{
    bool test = false;
    int i =0;
    while(test==false)
    {
    map<string, int>::iterator j = m_stats.begin();
    while(j!=m_stats.end())
    {
        if(stat==j->first)
        {
            i = j->second;
            test= true;
            break;
        }
    }
    }
    return i;
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
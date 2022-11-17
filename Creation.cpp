#include "Creation.hpp"
#include "Setup.hpp"
using namespace std;

Setup::Setup()
{
    ifstream fichier("Liste_texte.txt", ios::in);
    string l;
    while(getline(fichier,l))
    {
        m_map.insert(make_pair(l, l+".txt"));
        //cout << l <<m_map.at(l) << endl;
    }
    lire("Introduction");
{

}
}
void Setup::lire(string s)
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

void Setup::creation()
{
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
    cout << "Votre race:"<< endl;
    cin >> race;
    fflush(stdin);
    m_race=race;
    cout << "Votre age:"<< endl;
    cin >> age;
    fflush(stdin);
    m_age=age;
    vector<pair<string, int>> stats = {{"INT",0},{"AGI",0},{"VIT",0},{"CHA",0},{"CON",0}};
    for(int i=0;i<5;i++)
    {
        int valeur = rand()%20+1;
        stats.at(i).second = valeur;

    }
    m_inventaire.setPoidsMax((stats[4].second)*15);
    m_stats = stats;
    m_vie = stats[4].second*50;
    ofstream MyExcelFile;
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app);
    MyExcelFile << "\n" + getNom() + ";" ;
    MyExcelFile << getAge() << " ans;";
    MyExcelFile <<  getRace() + ";";
    for(int j=0;j<5;j++)
    {
        MyExcelFile << stats[j].second << ";" ;
        fflush(stdin);
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
int Personnage::ValeurStat(int stat)
{
    bool test = false;
    while(test==false)
    {
        if(stat<0 || stat>4)
        {
            cout << "La valeur est incorrect, rentrez une valeur entre 0 et 4" << endl;
            cin >> stat;
        }
        else
        {
            test=true;
        }
    }
    return m_stats[stat].second;
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
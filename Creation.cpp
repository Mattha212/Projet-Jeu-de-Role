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

int PairCountFelement(vector<pair<string, int>> v,string a)
{
    int nb =0;
    for(int i=0;i<v.size();i++)
    {   
        if(v.at(i).first==a)nb++; 
    }
    return nb;
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

    for(int it=0;it<p.getStats().size();it++)
    {
    MyExcelFile << p.ValeurStat(p.getStats()[it].first) << ";";
    } 
    MyExcelFile << p.getVie() << ";";
    MyExcelFile << "\n";

    MyExcelFile.close();
}

Personnage ChargerPerso(string nom)
{
    ifstream MyExcelFile ;
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app); 
    string line, word; int i =1;string  race; int age; vector<pair<string, int>> stat(5);
    bool test = false;
    while(getline(MyExcelFile, line)  && !test)
    {
    stringstream str(line), ss;
    getline(str, word, ';');
    if(word==nom)
    {
        while(getline(str, word, ';') && i<8)
        {
            switch(i)
            {
                case 1:age = stoi(word);
                break;
                case 2:race = word;
                break;
                case 3:stat.at(0)=make_pair("AGI",stoi(word));break;
                case 4:stat.at(1)=make_pair("CHA",stoi(word));break;
                case 5:stat.at(2)=make_pair("CON",stoi(word));break;
                case 6:stat.at(3)=make_pair("INT",stoi(word));break;
                case 7:stat.at(4)=make_pair("VIT",stoi(word));test=true;break;
            }         
            i++;   
        }
    }
    }
    Inventaire inv  = Inventaire(stat.at(2).second);
    inv.afficherInventaire();
    //inv.addObjet(ob);
    Personnage p = Personnage(nom,age,race,stat,inv);
    p.afficheStats();
    return p;
}

/**
 * It creates a character and saves it in a csv file.
 */
void Personnage::CreerPersonnage()
{
    fflush(stdin);
    srand((unsigned) time(NULL));
    vector<pair<string,int>> v1(5);
    m_stats =v1;
    m_stats[0].first="AGI";m_stats[1].first="CHA";m_stats[2].first="CON";m_stats[3].first="INT";m_stats[4].first="VIT";
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
    m_stats.at(0).second =m_stats.at(1).second=m_stats.at(2).second=m_stats.at(3).second=m_stats.at(4).second=-1;
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
            int its = 0;
            for(int i=0;i<5;i++)
            {
                if(m_stats.at(i).first == a)
                {
                    its = i;
                }
            }
            
            if(m_stats.at(its).second>0)
            {
                v[m_stats.at(its).second]++;
                m_stats.at(its).second = b;
                v[b]--;
            }
            else{
                m_stats.at(its).second=b;
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
    m_inventaire.setPoidsMax((m_stats.at(2).second)*15);
    m_vie = (m_stats.at(2).second)*50;
}

Personnage::Personnage()
{
    m_nom= "rien";
    m_age= 0;
    m_race = "rien";
}
Personnage::Personnage(string nom, int age ,string race, vector<pair<string, int>> stats, Inventaire stuff)
{
        vector<pair<string, int>> v1(5);
        m_stats = v1;
        m_nom = nom;
        m_age = age;
        m_race = race;
        m_vie = (stats.at(2).second)*50;
        m_stats.at(0)=stats.at(0); m_stats.at(2)=stats.at(2); m_stats.at(3)=stats.at(3); m_stats.at(4)=stats.at(4); m_stats.at(1)=stats.at(1);
        if(stuff.getPoidsTotal()>0)
        {
        map<string, Objet>::iterator it = stuff.getMap().begin();
        while(it!=stuff.getMap().end())
        {
            m_inventaire.addObjet(it->second);
        }
        }
        else m_inventaire = Inventaire();
}
vector<pair<string,int>> Personnage::getStats()
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
            m_stats.at(2).second ++; //CON
            m_stats.at(4).second +=3 ; //VIT
            m_stats.at(3).second --; //INT
        }
        else if(race == "orc") 
        {
            m_stats.at(1).second -=5; //CHA
            m_stats.at(2).second +=2; //CON
            m_stats.at(0).second +=2; //AGI
            m_stats.at(4).second +=2; //VIT

        }
        else if(race == "humain") 
        {
            m_stats.at(0).second +=2; //AGI
            m_stats.at(1).second +=2; //CHA
            m_stats.at(2).second -=2; //CON
        }
    
}

int Personnage::ValeurStat(string stat)
{

    for(int j=0; j<5; j++)
    {
        if(m_stats.at(j).first==stat)
        {
            return m_stats.at(j).second;
        }
    }

} 

void Personnage::afficheStats()
{
for(int i=0;i<m_stats.size();i++) 
{
    cout << m_stats[i].first << ": " << ValeurStat(m_stats[i].first) << ";";
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


Inventaire::Inventaire(int force)
{
map <string, Objet> m_inventaire;
m_poidsmax = force *10;
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
int Inventaire::getPoidsTotal()
{
    return m_poidsTotal;
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
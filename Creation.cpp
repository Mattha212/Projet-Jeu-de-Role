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
int PairCountFelement(Stats v,string a)
{
    int nb =0;
    for(int i=0;i<v.getSize();i++)
    {   
        if(v.getChar(i)==a)nb++; 
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

    for(int it=0;it<5;it++)
    {
    MyExcelFile << p.getStats().getStatfromIndex(it) <<";";
    } 
    MyExcelFile << p.getVie() << ";";
    MyExcelFile << "\n";

    MyExcelFile.close();
}

Personnage ChargerPerso(string nom)
{
    ifstream MyExcelFile ;
    MyExcelFile.open("C:\\Users\\wyzma\\Documents\\VSCODE\\C++\\Test_JDR\\test.csv", fstream::app); 
    string line, word; int i =1;string  race; int age; int stat[5];
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
                case 3:stat[0]=stoi(word);break;
                case 4:stat[1]=stoi(word);break;
                case 5:stat[2]=stoi(word);break;
                case 6:stat[3]=stoi(word);break;
                case 7:stat[4]=stoi(word);test=true;break;
            }         
            i++;
        }
    }
    }
    Inventaire inv  = Inventaire(stat[2]);
    Stats s = Stats(stat, 5);
    Personnage p = Personnage(nom,age,race,stat,inv);
    return p;
}
void Personnage::CreerPersonnage()
{
    m_stats = Stats();
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
    m_inventaire.setPoidsMax((m_stats.getStatfromString("CON"))*15);
    m_vie = (m_stats.getStatfromString("CON"))*50;
}
Personnage::Personnage()
{
    m_nom= "rien";
    m_age= 0;
    m_race = "rien";
}
Personnage::Personnage(string nom, int age ,string race, int stats[],Inventaire stuff)
{
        m_stats = Stats(stats,5);
        m_nom = nom;
        m_age = age;
        m_race = race;
        m_vie = (m_stats.getStatfromString("CON"))*50;
        m_inventaire = Inventaire(m_stats.getStatfromString("CON"));
        if(stuff.getPoidsTotal()>0)
        {
        map<string, Objet>::iterator it = stuff.getMap().begin();
        while(it!=stuff.getMap().end())
        {
            m_inventaire.addObjet(it->second);
        }}
        
        
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


Stats::Stats()
{
    m_size = 5;
    int i =-1;
    vector<pair<string, int>> v(m_size);
    v[0] = make_pair("AGI",i);
    v[1] = make_pair("CHA",i);
    v[2] = make_pair("CON",i);
    v[3] = make_pair("INT",i);
    v[4] = make_pair("VIT",i);
    m_stats=v;
}
int Stats::getSize()
{
    return m_size;
}
Stats::Stats(int tab[], int size)
{
    m_size = size;
    try
    {
        if(m_size==5){
            vector<pair<string, int>> v(5);
            v[0] = make_pair("AGI",tab[0]);
            v[1] = make_pair("CHA",tab[1]);
            v[2] = make_pair("CON",tab[2]);
            v[3] = make_pair("INT",tab[3]);
            v[4] = make_pair("VIT",tab[4]);
            m_stats=v;
        }
    
        else throw (size);
    }
    catch(int size){
        cout << "La taille du tableau n'est pas bonne! Il doit avoir 5 elements!" << endl;
        cout << "La taille actuelle est "<< size<< endl;
    }
}
int Stats::getStatfromString(string a)
{
    for(int i=0;i<(int)m_stats.size();i++)
    {
        if(m_stats[i].first==a) return m_stats[i].second;
    }
}
int Stats::getStatfromIndex(int a)
{
    return m_stats[a].second;
}
void Stats::AfficheStats()
{
    for(int i=0;i<(int)m_stats.size();i++)
    {
        cout << m_stats[i].first << ": " << m_stats[i].second << " ";
    }
}
string Stats::getChar(int index)
{
    return m_stats[index].first;
}
void Stats::SetStat(string a, int b)
{
    for(int i=0;i<(int)m_stats.size();i++)
    {
        if(m_stats[i].first==a)  m_stats[i].second = b;
    }
}

Arme::Arme() : Objet(1, "tuyau nul")
{
    m_degats = 10;
    m_materiau = "fer de merde";
    m_equipee = false;
}
Arme::Arme(string nom, int poids, int degats, string materiau): Objet(poids, nom)
{
    m_degats= degats;
    m_materiau = materiau;
    m_equipee = false;
}
int Arme::getDegats()
{
    return m_degats;
}
string Arme::getMateriau()
{
    return m_materiau;
}
void Arme::equipe_OR_desequipe()
{
    m_equipee = !m_equipee;
}




Armure::Armure(): Objet(1, "vieux tissu")
{
    m_materiau = "tissu de merde";
    m_protection = 5;
    m_equipee = false;
}
Armure::Armure(string nom, int poids, int protection, string materiau): Objet(poids, nom)
{
    m_materiau= materiau;
    m_protection = protection;
    m_equipee = false;
}
int Armure::getProtection()
{
    return m_protection;
}
string Armure::getMateriau()
{
    return m_materiau;
}
void Armure::equipe_OR_desequipe()
{
    m_equipee = !m_equipee;
}





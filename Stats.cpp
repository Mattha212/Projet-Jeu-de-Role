#include "Stats.hpp"
using namespace std;

Stats::Stats()
{
    m_size = 5;
    int i =-1;
    {
        map<std::string, int> v;
        v["AGI"] = i; 
        v["CHA"] = i; 
        v["CON"] = i; 
        v["INT"] = i; 
        v["VIT"] = i; 
        fill(m_valeurs.begin(), m_valeurs.end(), i);
        m_tabstat = v;
    }
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
            map<std::string, int> v;
            v["AGI"] = tab[0];
            v["CHA"] = tab[1];
            v["CON"] = tab[2];
            v["INT"] = tab[3];
            v["VIT"] = tab[4];
            m_valeurs.push_back(v["AGI"]);
            m_valeurs.push_back(v["CHA"]);
            m_valeurs.push_back(v["CON"]);
            m_valeurs.push_back(v["INT"]);
            m_valeurs.push_back(v["VIT"]);
            m_tabstat =v;
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
    return m_tabstat[a];
    
    return 0;
}
void Stats::AfficheStats()
{
    for(auto it = m_tabstat.begin(); it!= m_tabstat.end(); ++it)
    {
        cout << it->first << ": " << it->second << " ";
    }
}

void Stats::SetStat(string a, int b)
{
         m_tabstat[a]= b;
}

//void Stats::applyRaceModifier(string race) {
//    enum classe_code {
//        cElfe,
//        cHumain,
//        cOrc
//    };
//    auto type_race = [&](string l_race)-> classe_code {
//        if (l_race == "Elfe") return cElfe;
//        if (l_race == "Humain") return cHumain;
//        if (l_race == "Orc") return cOrc;
//        };
//    switch (type_race(race)) {
//    case cElfe:
//        m_tabstats
//    }
//
//
//}
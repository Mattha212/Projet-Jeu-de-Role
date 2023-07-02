#include "Stats.hpp"
using namespace std;

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
    return 0;
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

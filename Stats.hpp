#ifndef Stats_Header
#define Stats_Header

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
class Stats
{
    private:
    std::map<std::string, int> m_tabstat;
    std::vector<int> m_valeurs{0,0,0,0,0};
    int m_size;
    public:
    Stats();
    Stats(int tab[], int size);
    std::map<std::string, int> getStat() { return m_tabstat; }
    std::vector<int> getValeurs() { return m_valeurs; }

    int CountFelement(std::string wantedstat) {
        
        return count_if(m_tabstat.begin(), m_tabstat.end(), [&](auto index) {
            return index.first == wantedstat;
            });
    }
    void applyRaceModifier(std::string race);
    int getStatfromString(std::string a);
    int getSize();
    void AfficheStats();
    void SetStat(std::string a, int b);
    ~Stats(){};
};
#endif
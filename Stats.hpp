#include <bits/stdc++.h>
class Stats
{
    private:
    std::vector<std::pair<std::string, int>> m_stats;
    int m_size;
    public:
    Stats();
    Stats(int tab[], int size);
    std::string getChar(int index);
    int getStatfromString(std::string a);
    int getStatfromIndex(int a);
    int getSize();
    void AfficheStats();
    void SetStat(std::string a, int b);
    ~Stats(){};
};
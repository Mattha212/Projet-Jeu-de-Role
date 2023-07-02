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
#endif
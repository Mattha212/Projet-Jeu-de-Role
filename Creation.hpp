#include "Inventaire.hpp"


class Personnage
{
    private:
        std::string m_nom;
        int m_age;
        std::string m_race;
        int m_vie;
        std::vector<std::pair<std::string,int>> m_stats;
        Inventaire m_inventaire;
    public:
        Personnage();
        std::string getNom();
        void ModifRace(std::vector<std::pair<std::string,int>> stat, std::string race);
        int getAge();
        std::string getRace();
        int ValeurStat(int stat);
        void recupererObjet(Objet obj);
        void jeterObjet(Objet obj);
        Inventaire getInventaire();
        ~Personnage(){};


};






#include "Inventaire.hpp"


class Personnage
{
    private:
        std::string m_nom;
        int m_age;
        std::string m_race;
        int m_vie;
        std::map<std::string, int> m_stats;
        Inventaire m_inventaire;
    public:
        Personnage();
        std::string getNom();
        void ModifRace(std::map<std::string, int> stat, std::string race);
        int getAge();
        std::string getRace();
        int ValeurStat(std::string stat);
        void recupererObjet(Objet obj);
        void jeterObjet(Objet obj);
        Inventaire getInventaire();
        ~Personnage(){};


};






#include "Inventaire.hpp"


class Personnage
{
    private:
        std::string m_nom;
        int m_age;
        std::string m_race;
        int m_vie;
        Inventaire m_inventaire;
    protected:
        
    public:
        Personnage();
        Personnage(std::string nom, int age ,std::string race, std::map<std::string, int> stats, Inventaire stuff);
        void CreerPersonnage();
        std::string getNom();
        void ModifRace(std::string race);
        int getAge();
        int getVie();
        std::map<std::string, int> getStats();
        std::string getRace();
        int ValeurStat(std::string stat);
        void afficheStats();
        void recupererObjet(Objet obj);
        void jeterObjet(Objet obj);
        Inventaire getInventaire();
        std::map<std::string, int> m_stats;
        ~Personnage(){};


};






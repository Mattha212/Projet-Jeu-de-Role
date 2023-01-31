#include "Inventaire.hpp"
#include "Stats.hpp"
class Personnage
{
    private:
        std::string m_nom;
        int m_age;
        std::string m_race;
        int m_vie;
        Inventaire m_inventaire;
        std::vector<std::pair<std::string, int>> m_stats;        
    public:
        Personnage();
        Personnage(std::string nom, int age ,std::string race, std::vector<std::pair<std::string, int>> stats, Inventaire stuff);
        void CreerPersonnage();
        std::string getNom();
        void ModifRace(std::string race);
        int getAge();
        int getVie();
        std::vector<std::pair<std::string, int>> getStats();
        std::string getRace();
        int ValeurStat(std::string stat);
        void afficheStats();
        void recupererObjet(Objet obj);
        void jeterObjet(Objet obj);
        Inventaire getInventaire();
        ~Personnage(){};


};




















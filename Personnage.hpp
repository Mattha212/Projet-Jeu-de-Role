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
        Stats m_stats;      
    public:
        Personnage();
        Personnage(std::string nom, int age ,std::string race, int stats[], Inventaire stuff);
        void CreerPersonnage();
        std::string getNom();
        void ModifRace(std::string race);
        int getAge();
        int getVie();
        Stats getStats();
        std::string getRace();
        void recupererObjet(Objet obj);
        void jeterObjet(Objet obj);
        Inventaire getInventaire();
        ~Personnage(){};


};




















#ifndef Personnage_Header
#define Personnage_Header

#include "Inventaire.hpp"
#include "Stats.hpp"

class Personnage
{
    private:
        std::string m_nom;
        int m_age;
        std::string m_race;
        int m_vie;
        Inventaire *m_inventaire;
        Stats m_stats;      
    public:
        Personnage();
        Personnage(std::string name, int age, std::string race, int* stats, Inventaire stuff);
        Personnage(Personnage const& PersoACopier);
        ~Personnage() { delete [] m_inventaire; };
        void swap(Personnage& autre) noexcept {
            using std::swap;
            swap(m_nom, autre.m_nom);
            swap(m_age, autre.m_age);
            swap(m_race, autre.m_race);
            swap(m_inventaire, autre.m_inventaire);
            swap(m_stats, autre.m_stats);

        }
        Personnage& operator=(const Personnage& autre) {
            Personnage{ autre }.swap(*this);
            return *this;
        }
        


        void CreerPersonnage();
        std::string getNom();
        void ModifRace(std::string race);
        int getAge();
        int getVie();
        void setVie(int v);
        Stats getStats();
        bool IsAlive();
        std::string getRace();
        void recupererObjet(Objet obj);
        void jeterObjet(Objet obj);
        Inventaire getInventaire();
        void Attaquer(Personnage &cible);
        void PrendreDegats(int degats);
        void Sauvegarde();

};

#endif


















#ifndef Personnage_Header
#define Personnage_Header

#include "Inventaire.cpp"
#include "Stats.cpp"
#include <bits/stdc++.h>

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
        Personnage(Personnage const& PersoACopier);
        Personnage(std::string name, int age, std::string race, int *stats, Inventaire stuff);
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
        ~Personnage(){delete m_inventaire;};
};

#endif


















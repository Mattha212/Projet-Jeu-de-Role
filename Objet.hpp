#ifndef Objet_Header
#define Objet_Header

#include <bits/stdc++.h>
#include <stdlib.h>
#include <iostream>
class Objet
{
    private:
        int m_poids;
        std::string m_nom;  
        int m_nb_element;
        int m_type; //0 pour arme, 1 pour armure, 2 pour potion

    public:
        Objet();
        Objet(int poids, std::string nom, int type);
        int getPoids();
        std::string getNom();
        void setNom(std::string newnom);
        void setPoids(int newpoids);
        int getNbElement();
        void setNbElement(int newNbElement);
        int getType();
        ~Objet(){};
};
#endif
#ifndef Arme_Header
#define Arme_Header

class Arme: public Objet
{
    private:
        int m_degats;
        std::string m_materiau;
        bool m_equipee;

    public:
        Arme();
        Arme(std::string nom, int poids, int degats, std::string materiau);
        int getDegats();
        std::string getMateriau();
        void equipe_OR_desequipe();
        ~Arme(){};
};
#endif

#ifndef Armure_Header
#define Armure_Header

class Armure: public Objet
{
    private:
        int m_protection;
        std::string m_materiau;
        bool m_equipee;
    public:
        Armure();
        Armure(std::string nom, int poids, int protection, std::string materiau);
        int getProtection();
        std::string getMateriau();
        void equipe_OR_desequipe();
        ~Armure(){};
};
#endif
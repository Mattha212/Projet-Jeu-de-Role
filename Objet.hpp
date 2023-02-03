#include <bits/stdc++.h>



class Objet
{
private:
    int m_poids;
    std::string m_nom;  
    int m_nb_element;


public:
    Objet();
    Objet(int poids, std::string nom);
    int getPoids();
    std::string getNom();
    void setNom(std::string newnom);
    void setPoids(int newpoids);
    int getNbElement();
    void setNbElement(int newNbElement);
    ~Objet(){};
};

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

class Armure: public Objet
{
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
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
};
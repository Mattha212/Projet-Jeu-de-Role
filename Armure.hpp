#include "Objet.hpp"


class Armure: private Objet
{
    int m_protection;
    std::string materiau;
    bool equipee;
public:
    Armure();
    Armure(std::string nom, int poids, int protection, std::string materiau);
    std::string getNom();
    int getPoids();
    int getProtection();
    std::string getMateriau();
    void equipe_OR_desequipe();
    ~Armure(){};
};
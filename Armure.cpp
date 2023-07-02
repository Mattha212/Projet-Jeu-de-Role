#include "Objet.hpp"
using namespace std;

Armure::Armure(): Objet(1, "vieux tissu", 1)
{
    m_materiau = "tissu de merde";
    m_protection = 5;
    m_equipee = false;
}
Armure::Armure(string nom, int poids, int protection, string materiau): Objet(poids, nom, 1)
{
    m_materiau= materiau;
    m_protection = protection;
    m_equipee = false;
}
int Armure::getProtection()
{
    return m_protection;
}
string Armure::getMateriau()
{
    return m_materiau;
}
void Armure::equipe_OR_desequipe(){
    m_equipee = !m_equipee;
}

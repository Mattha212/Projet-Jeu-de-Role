
#include "Objet.hpp"
using namespace std;

Arme::Arme() : Objet(1, "tuyau nul", 0)
{
    m_degats = 10;
    m_materiau = "fer de merde";
    m_equipee = false;
}
Arme::Arme(string nom, int poids, int degats, string materiau): Objet(poids, nom, 0)
{
    m_degats= degats;
    m_materiau = materiau;
    m_equipee = false;
}
int Arme::getDegats()
{
    return m_degats;
}
string Arme::getMateriau()
{
    return m_materiau;
}
void Arme::equipe_OR_desequipe()
{
    m_equipee = !m_equipee;
}

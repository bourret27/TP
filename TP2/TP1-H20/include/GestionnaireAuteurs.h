#ifndef GESTIONNAIREAUTEURS_H
#define GESTIONNAIREAUTEURS_H

#include <string>
#include <vector>
#include "Auteur.h"

class GestionnaireAuteurs
{
public:
    GestionnaireAuteurs();

    Auteur* chercherAuteur(const std::string& nomAuteur);
    bool chargerDepuisFichier(const std::string& nomFichier);

    std::size_t getNbAuteurs() const;

    friend std::ostream& operator<<(std::ostream& flux,
                                    const GestionnaireAuteurs& gestionnaireAuteur);
    bool operator+=(const Auteur& auteur);

    static constexpr std::size_t NB_AUTEURS_MAX = 16;

private:
    bool lireLigneAuteur(const std::string& ligne);

    std::vector<Auteur> auteurs_;
    std::size_t nbAuteurs_;
};

#endif // GESTIONNAIREAUTEURS_H
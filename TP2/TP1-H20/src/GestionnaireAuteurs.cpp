/*
* Classe qui définit un gestionnaire auteurs.
* \file   GestionnaireAuteurs.cpp
* \author William Bourret et Philippe De Blois
* \date   10 fevrier 2020
* Créé le 10 fevrier 2020
*/

#include "GestionnaireAuteurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur de la classe GestionnaireAuteurs
GestionnaireAuteurs::GestionnaireAuteurs()
    : auteurs_(std::vector<Auteur>(NB_AUTEURS_MAX)), // ne pas changer. le vecteur doit etre initialiser a 16 ici
      nbAuteurs_(0)
{
}

//! Surcharge de l'opérateur += qui ajoute un auteur à la liste des auteurs
//! \param auteur L'auteur à ajouter
//! \return       Un bool représentant si l'opération a fonctionnné
bool GestionnaireAuteurs::operator+=(const Auteur& auteur)
{
    if (nbAuteurs_ >= NB_AUTEURS_MAX)
    {
        return false;
    }

    auteurs_[nbAuteurs_++] = auteur;
    return true;
}

//! Méhode qui cherche un auteur par son nom complet
//! \param nomAuteur Le nom de l'auteur à trouver
//! \return          Un pointeur vers l'auteur. Le pointeur est nullptr si l'auteur n'existe pas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
    for (std::size_t i = 0; i < nbAuteurs_; i++)
    {
        if (nomAuteur == auteurs_[i])
        {
            return &auteurs_[i];
        }
    }

    return nullptr;
}

//! Méthode qui prend un nom de fichier en paramètre et qui charge les auteurs
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool représentant si le chargement a été un succès
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        nbAuteurs_ = 0;
        auteurs_.clear();
        auteurs_ = std::vector<Auteur>(NB_AUTEURS_MAX);
        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            if (lireLigneAuteur(ligne) == false)
            {
                return false;
            }
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Surcharge de l'opérateur << qui affiche la liste des auteurs
//! \param stream Le stream dans lequel afficher
//! \param gestionnaireAuteurs Le gestionnaire d'auteurs à afficher
//! \return Une référence du flux où sera écrit le gestionnaire
std::ostream& operator<<(std::ostream& flux, const GestionnaireAuteurs& gestionnaireAuteurs)
{
    for (std::size_t i = 0; i < gestionnaireAuteurs.nbAuteurs_; ++i)
    {
        flux << gestionnaireAuteurs.auteurs_[i] << std::endl;
    }
    return flux;
}

//! Méthode qui retourne le nombre d'auteurs
//! \return Le nombre d'auteurs
std::size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return nbAuteurs_;
}

//! Méthode qui ajoute un auteur avec un string
//! \param ligne Le string qui comporte tous les attributs de l'auteur
bool GestionnaireAuteurs::lireLigneAuteur(const std::string& ligne)
{
    std::istringstream stream(ligne);
    std::string nomAuteur;
    unsigned int age;

    // Pour extraire tout ce qui se trouve entre "" dans un stream,
    // il faut faire stream >> std::quoted(variable)

    if (stream >> std::quoted(nomAuteur) >> age)
    {
        return ((*this) += Auteur(nomAuteur, age));
    }
    return false;
}
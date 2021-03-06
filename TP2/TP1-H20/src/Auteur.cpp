/*
* Classe qui définit un auteur.
* \file   Auteur.cpp
* \author William Bourret et Philippe De Blois
* \date   10 fevrier 2020
* Créé le 10 fevrier 2020
*/

#include "Auteur.h"
#include <iostream>

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Année de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbFilms_(0)
{
}

//! Surcharge de l'opérateur << qui affiche un auteur
//! \param stream Le stream dans lequel afficher
//! \param auteur L'auteur à afficher
//! \return Le flux dans lequel l'auteur s'affiche
std::ostream& operator<<(std::ostream& flux, const Auteur& auteur)
{
    return flux << "Nom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
             << " | Nombre de films: " << auteur.nbFilms_;
}

bool operator==(const std::string& nom, const Auteur& auteur)
{
    return nom == auteur.nom_;
}

bool Auteur::operator==(const std::string& nom)
{
    return this -> nom_ == nom;
}

//! Méthode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'année de naissance de l'auteur
//! \return L'année de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Méthode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbFilms() const
{
    return nbFilms_;
}

//! Méthode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbFilms(unsigned int nbFilms)
{
    nbFilms_ = nbFilms;
}
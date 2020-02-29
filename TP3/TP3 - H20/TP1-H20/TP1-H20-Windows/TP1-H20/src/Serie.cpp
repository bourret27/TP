// To do
#include "Serie.h"

// To do              Pointeur vers l'auteur du serie
Serie::Serie(Auteur* auteur) :
    Media(auteur, TypeMedia::Serie)
    // To do
{
}

// To do
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur) :
    Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Serie)
    // To do
{
}

// To do
Serie::Serie(const Serie& serie) :
    Media(serie)
    // To do
{
    // To do
}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
    Media::afficher(os);
    return os;
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    return std::make_unique<Serie>(*this);
}
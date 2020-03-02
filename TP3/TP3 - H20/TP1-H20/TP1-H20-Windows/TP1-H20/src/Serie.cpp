// To do
#include "Serie.h"

// To do              Pointeur vers l'auteur du serie
Serie::Serie(Auteur* auteur) :
    Media(auteur, TypeMedia::Serie),
	GestionnaireSaisons()
    // To do
{
}

// To do
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur) :
    Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Serie),
	GestionnaireSaisons()
    // To do
{
}

// To do
Serie::Serie(const Serie& serie) :
    Media(serie),
	GestionnaireSaisons()
    // To do
{
    // To do
}

// To do
std::ostream& Serie::afficher(std::ostream& os) const
{
    Media::afficher(os);
	for (std::size_t i = 0; i < getNbSaisons(); i++)
	{
		os << *saisons_[i];
	}
    return os;
}

// To do
std::unique_ptr<Media> Serie::clone() const
{
    return std::move(std::make_unique<Serie>(*this));
}
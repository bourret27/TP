// To do
#include "Media.h"
#include "Film.h"

// To do
Film::Film(Auteur* auteur):
    
// To do
{

}

// To do
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
    bool estRestreintParAge, Auteur* auteur, const std::string& duree) :
    Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Film),
    duree_(duree)
    // To do
{
}

// To do
std::ostream& Film::afficher(std::ostream& os) const
{
    Media::afficher(os);
    os << "\tDurée: " << duree_ << "\n";
    return os;
    // To do
}

// To do
std::istream& Film::lire(std::istream& is)
{
    // To do
}

// To do
std::unique_ptr<Media> Film::clone() const
{
    return std::make_unique<Media>(*this);
}

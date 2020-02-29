// To do
#include "Media.h"
#include "Film.h"

// To do
Film::Film(Auteur* auteur) :
    Media(auteur, TypeMedia::Film),
    duree_("00:00:00")
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
    Media::lire(is);
    is >> duree_;
    return is;

}

// To do
std::unique_ptr<Media> Film::clone() const
{
    return Media::clone();
}

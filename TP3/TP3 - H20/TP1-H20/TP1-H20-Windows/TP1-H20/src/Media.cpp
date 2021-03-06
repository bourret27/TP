#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui représente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui représente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

// To do
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia) :
    nom_("NomMedia"),
    anneeDeSortie_(0),
    genre_(Genre::first_),
    pays_(Pays::first_),
    estRestreintParAge_(false),
    auteur_(auteur),
    typeMedia_(typeMedia)
// To do
{

}

// To do
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia) :
    nom_(nom),
    anneeDeSortie_(anneeDeSortie),
    genre_(genre),
    pays_(pays),
    estRestreintParAge_(estRestreintParAge),
    auteur_(auteur),
    typeMedia_(typeMedia)
{
}

// To do
Media::Media(const Media& media) : 
    //Media(serie.nom_, serie.anneeDeSortie_, serie.genre_, serie.pays_, 
    //    serie.estRestreintParAge_, serie.auteur_, serie.typeMedia_),
    nom_(media.nom_),
    anneeDeSortie_(media.anneeDeSortie_),
    genre_(media.genre_),
    pays_(media.pays_),
    estRestreintParAge_(media.estRestreintParAge_),
    auteur_(media.auteur_),
    typeMedia_(media.typeMedia_),
    paysRestreints_(media.paysRestreints_)
{

}


// To do
Media::~Media()
{
	supprimerPaysRestreints();
}

// To do
void Media::ajouterPaysRestreint(Pays pays)
{
    paysRestreints_.push_back(pays);
}

// To do
void Media::supprimerPaysRestreints()
{
    paysRestreints_.clear();
}

// To do
bool Media::estRestreintDansPays(Pays pays) const
{
    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        if (paysRestreints_[i] == pays)
        {
            return true;
        }
    }
    return false;
}

// To do
bool Media::estRestreintParAge() const
{
    return estRestreintParAge_;
}

// To do
std::ostream& Media::afficher(std::ostream& os) const
{
    os << nom_ << "\n\tDate de sortie: " << anneeDeSortie_
        << "\n\tGenre: " << getGenreString(genre_) << "\n\tAuteur: " << auteur_->getNom()
        << "\n\tPays: " << getPaysString(pays_)
        << (paysRestreints_.size() == 0 ? "\n\tAucun pays restreint." : "\n\tPays restreints:");

    for (std::size_t i = 0; i < paysRestreints_.size(); i++)
    {
        os << "\n\t\t" << getPaysString(paysRestreints_[i]);
    }
    os << '\n';

    return os;
}

// To do
std::ostream& operator<<(std::ostream& os, const Media& media)
{
    return media.afficher(os);
}

// To do
Media::Genre Media::getGenre() const
{
    return genre_;
}

// To do
const std::string& Media::getNom() const
{
    return nom_;
}

// To do
Media::TypeMedia Media::getTypeMedia() const
{
    return typeMedia_;
}

Auteur* Media::getAuteur() const
{
	return auteur_;
}

// To do
std::istream& Media::lire(std::istream& is)
{
    //int typeMediaValeurEnum = 0;
    int genreValeurEnum = 0;
    int paysValeurEnum = 0;
    is >> /*typeMediaValeurEnum >> *auteur_ >> */ std::quoted(nom_) >> anneeDeSortie_ 
        >> genreValeurEnum >> paysValeurEnum >> estRestreintParAge_;
    //typeMedia_ = to_enum<TypeMedia>(typeMediaValeurEnum);
    genre_ = to_enum<Genre>(genreValeurEnum);
    pays_ = to_enum<Pays>(paysValeurEnum);
    return is;
}

// To do
std::istream& operator>>(std::istream& is, Media& media)
{
    return media.lire(is);
}

// To do
std::unique_ptr<Media> Media::clone() const
{
    return std::move(std::make_unique<Media>(*this));
}
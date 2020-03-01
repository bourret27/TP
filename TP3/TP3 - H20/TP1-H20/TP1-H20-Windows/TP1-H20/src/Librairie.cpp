#include "Librairie.h"
#include "GestionnaireAuteurs.h"
#include "GestionnaireSaisons.h"

// To do
Librairie::Librairie(const Librairie& librairie)
{
    for (std::size_t i = 0; i < librairie.getNbMedias(); i++)
    {
		medias_.push_back(std::move(librairie.getMedias()[i]->clone()));
    }
}

// To do
Librairie& Librairie::operator=(const Librairie& librairie)
{
	if (&librairie == this)
		return *this;
	medias_.clear();
	for (std::size_t i = 0; i < librairie.getNbMedias(); i++)
	{
		medias_.push_back(std::move(librairie.getMedias()[i]->clone()));
	}
	return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

// To do
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
	Media* film = chercherMedia(nomFilm, Media::TypeMedia::Film);
	return dynamic_cast<Film*>(film);
}

// To do
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
	Media* serie = chercherMedia(nomSerie, Media::TypeMedia::Serie);
	return dynamic_cast<Serie*>(serie);
}

// To do
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
	Serie* serie = chercherSerie(nomSerie);
	*serie += std::move(saison);
}

// To do
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
	Serie* serie = chercherSerie(nomSerie);
	*serie -= numSaison;
}

// To do
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
	Serie* serie = chercherSerie(nomSerie);
	serie->ajouterEpisode(numSaison, std::move(episode));
}


void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
	Serie* serie = chercherSerie(nomSerie);
	serie->retirerEpisode(numSaison, numEpisode);
}

//! Méthode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Nécessaire pour associer un serie à un
//! auteur.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
    GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		// Supprimer les vieux medias avant de lire les nouveaux
		medias_.clear();

		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (lireLigneMedia(ligne, gestionnaireAuteurs) == false)
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

//! Méthode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool représentant si le chargement a été un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
            if (!lireLigneRestrictions(ligne))
                return false;

        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

// To do
size_t Librairie::getNbMedias() const
{
    return medias_.size();
}

// To do
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    for (std::size_t i = 0; i < librairie.medias_.size(); i++)
    {
        os << librairie.medias_[i];
    }
    return os;
}

// To do
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    std::size_t indexMedia = MEDIA_INEXSISTANT;
    for (std::size_t i = 0; i < medias_.size() && indexMedia == MEDIA_INEXSISTANT; i++)
    {
        if (medias_[i]->getNom() == nomMedia)
            indexMedia = i;
    }
    return indexMedia;
}

// To do
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    medias_.push_back(std::move(media));
	return *this;
}

// To do
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    int indexMedia = trouverIndexMedia(nomMedia);
    medias_.erase(medias_.begin() + indexMedia);
	return *this;
}

// To do
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    Media* ptrMedia = nullptr;
    std::size_t indexMedia = trouverIndexMedia(nomMedia);
    for (std::size_t i = indexMedia; i < getNbMedias() && ptrMedia == nullptr; i++)
    {
        if (medias_[i]->getTypeMedia() == typeMedia)
        {
            ptrMedia = medias_[i].get();
        }
    }
    return ptrMedia;

}

// To do
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int typeMedia;
	std::string nomMedia;
	// Pour extraire tout ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> std::quoted(variable)
	if (stream >> typeMedia >> std::quoted(nomMedia))
	{
		Media* media = chercherMedia(nomMedia, to_enum<Media::TypeMedia>(typeMedia));
		if (media == nullptr)
		{
			// Media n'existe pas
			return false;
		}

		int paysValeurEnum;
		while (stream >> paysValeurEnum)
		{
			media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
		}
		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

// To do
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    return medias_;
}

// To do
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::string nomSerie;
	int numSaison = 0;
	Episode episode;
	if (is >> episode >> std::quoted(nomSerie) >> numSaison)
	{
		ajouterEpisode(nomSerie, numSaison, std::move(std::make_unique<Episode>(episode)));
		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::string nomSerie;
	Saison saison;
	if (is >> saison >> std::quoted(nomSerie))
	{
		ajouterSaison(nomSerie, std::move(std::make_unique<Saison>(saison)));
		return true;
	}
	return false;
}

// To do
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::string nomAuteur = "";
	if (is >> std::quoted(nomAuteur))
	{
		Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
		if (auteur == nullptr)
			return false;
		Serie serie(auteur);
		is >> serie;
		auteur->setNbMedias(auteur->getNbMedias() + 1);
		*this += std::move(serie.clone());
		return true;
	}/*
	if (is >> serie)
	{
		Auteur* auteur = gestionnaireAuteurs.chercherAuteur(serie.getAuteur()->getNom());
		if (auteur == nullptr)
		{
			return false;
		}
		auteur->setNbMedias(auteur->getNbMedias() + 1);
		*this += std::move(serie.clone());
		return true;
	}*/
	return false;
}

// To do
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
	std::string nomAuteur = "";
	if (is >> std::quoted(nomAuteur))
	{
		Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
		if (auteur == nullptr)
			return false;
		Film film(auteur);
		is >> film;
		auteur->setNbMedias(auteur->getNbMedias() + 1);
		*this += std::move(film.clone());
		return true;
	}
	/*Film film(nullptr);
	if (is >> film)
	{
		Auteur* auteur = gestionnaireAuteurs.chercherAuteur(film.getAuteur()->getNom());
		if (auteur == nullptr)
		{
			return false;
		}
		auteur->setNbMedias(auteur->getNbMedias() + 1);
		*this += std::move(film.clone());
		return true;
	}*/
	return false;
}

// To do
size_t Librairie::getNbFilms() const
{
    std::size_t nbFilms = 0;
    for (std::size_t i = 0; i < getNbMedias(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
            nbFilms++;
    }
    return nbFilms;
}

// To do
size_t Librairie::getNbSeries() const
{
    std::size_t nbSeries = 0;
    for (std::size_t i = 0; i < getNbMedias(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
            nbSeries++;
    }
    return nbSeries;
}

// To do
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
	std::size_t indexSerie = trouverIndexMedia(nomSerie);
	Serie* ptrSerie = dynamic_cast<Serie*>(medias_[indexSerie].get());
    //Serie* ptrSerie = chercherSerie(nomSerie);
	return ptrSerie->getNbSaisons();
}

// To do
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
	std::size_t indexSerie = trouverIndexMedia(nomSerie);
	Serie* ptrSerie = dynamic_cast<Serie*>(medias_[indexSerie].get());
	Saison* ptrSaison = ptrSerie->getSaison(numSaison);
	//Serie* ptrSerie = chercherSerie(nomSerie);
	return ptrSaison->getNbEpisodes();
}

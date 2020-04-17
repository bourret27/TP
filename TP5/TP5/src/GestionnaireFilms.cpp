/// Gestionnaire de films.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include "GestionnaireFilms.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Foncteurs.h"
#include "RawPointerBackInserter.h"

/// Constructeur par copie.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
GestionnaireFilms::GestionnaireFilms(const GestionnaireFilms& other)
{
    films_.reserve(other.films_.size());
    filtreNomFilms_.reserve(other.filtreNomFilms_.size());
    filtreGenreFilms_.reserve(other.filtreGenreFilms_.size());
    filtrePaysFilms_.reserve(other.filtrePaysFilms_.size());

    for (const auto& film : other.films_)
    {
		ajouterFilm(*film);
    }
}

/// Opérateur d'assignation par copie utilisant le copy-and-swap idiom.
/// \param other    Le gestionnaire de films à partir duquel copier la classe.
/// \return         Référence à l'objet actuel.
GestionnaireFilms& GestionnaireFilms::operator=(GestionnaireFilms other)
{
    std::swap(films_, other.films_);
    std::swap(filtreNomFilms_, other.filtreNomFilms_);
    std::swap(filtreGenreFilms_, other.filtreGenreFilms_);
    std::swap(filtrePaysFilms_, other.filtrePaysFilms_);
    return *this;
}

/// Affiche les informations des films gérés par le gestionnaire de films à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des films.
/// \param gestionnaireFilms    Le gestionnaire de films à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireFilms& gestionnaireFilms)
{
    outputStream << "Le gestionnaire de films contient " << gestionnaireFilms.getNombreFilms() << " films.\n"
                 << "Affichage par catégories:\n";

    for (const auto& [genre, listeFilms] : gestionnaireFilms.filtreGenreFilms_)
    {
        outputStream << "Genre: " << getGenreString(genre) << " (" << listeFilms.size() << " films):\n";
        for (std::size_t i = 0; i < listeFilms.size(); i++)
        {
            outputStream << '\t' << *listeFilms[i] << '\n';
        }
    }
    return outputStream;
}

/// Ajoute les films à partir d'un fichier de description des films.
/// \param nomFichier   Le fichier à partir duquel lire les informations des films.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireFilms::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        films_.clear();
        filtreNomFilms_.clear();
        filtreGenreFilms_.clear();
        filtrePaysFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string nom;
            int genre;
            int pays;
            std::string realisateur;
            int annee;

            if (stream >> std::quoted(nom) >> genre >> pays >> std::quoted(realisateur) >> annee)
            {
				ajouterFilm(Film{nom, static_cast<Film::Genre>(genre), static_cast<Pays>(pays), realisateur, annee});
            }
            else
            {
                std::cerr << "Erreur GestionnaireFilms: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur GestionnaireFilms: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/// Ajoute un film au gestionnaire.
/// \param film				   Le film à ajouter au gestionnaire.
/// \return                    Un booléen indiquant si le film a été ajouté ou s'il était déjà présent.
bool GestionnaireFilms::ajouterFilm(const Film& film)
{
	if (getFilmParNom(film.nom) != nullptr)
	{
		return false;
	}
	std::unique_ptr<Film> smartPtrFilm = std::make_unique<Film>(film);
	filtreNomFilms_.emplace(film.nom, smartPtrFilm.get());
	filtreGenreFilms_[film.genre].push_back(smartPtrFilm.get());
	filtrePaysFilms_[film.pays].push_back(smartPtrFilm.get());
	films_.push_back(std::move(smartPtrFilm));
	return true;
}

/// Supprime un film du gestionnaire.
/// \param utilisateur         Le film à supprimer du gestionnaire.
/// \return                    Un booléen indiquant si le film a été supprimé ou s'il n'était déjà pas présent.
bool GestionnaireFilms::supprimerFilm(const std::string& nomFilm)
{
	auto iterateurFilm = std::find_if(films_.begin(), films_.end(), [&nomFilm](const std::unique_ptr<Film> &ptrFilm) -> bool { return (*ptrFilm).nom == nomFilm; });
	// On aurait pu utiliser la méthode getFilmParNom avant de rechercher l'itérateur et retourner false si le film n'existe pas.
	// Toutefois, dans le cas où le film existe, on se retrouverait à faire la recherche du film deux fois dans deux conteneurs différents.
	// En faisant une seule recherche, même si elle est plus complexe (car on n'utilise pas les filtres stockés en tant qu'unordered_map),
	// on obtient un temps de recherche moyen plus bas, surtout considérant qu'en principe, les films devraient exister plus souvent
	// qu'autrement.
	if (iterateurFilm == films_.end())
	{
		return false;
	}
	filtreNomFilms_.erase(nomFilm);
	auto predicatFilm = [&nomFilm](const Film* ptrFilm) -> bool { return (*ptrFilm).nom == nomFilm; };
	std::vector<const Film*>& vecteurGenre = filtreGenreFilms_[(**iterateurFilm).genre];
	vecteurGenre.erase(std::remove_if(vecteurGenre.begin(), vecteurGenre.end(), predicatFilm));
	std::vector<const Film*>& vecteurPays = filtrePaysFilms_[(**iterateurFilm).pays];
	vecteurPays.erase(std::remove_if(vecteurPays.begin(), vecteurPays.end(), predicatFilm));
	films_.erase(iterateurFilm);
	return true;
}

/// Retourne le nombre de films dans le gestionnaire.
/// \return                    Le nombre de films dans le gestionnaire.
std::size_t GestionnaireFilms::getNombreFilms() const
{
	return films_.size();
}

/// Retourne un pointeur pointant vers le film selon le nom spécifié.
/// \param nom				   Le nom du film à chercher.
/// \return                    Le pointeur vers le film recherché. nullptr si pas trouvé.
const Film* GestionnaireFilms::getFilmParNom(const std::string& nom) const
{
	std::unordered_map<std::string, const Film*>::const_iterator iterateurFilm = filtreNomFilms_.find(nom);
	if (iterateurFilm == filtreNomFilms_.end())
	{
		return nullptr;
	}
	return iterateurFilm->second;
}

/// Retourne un vecteur de pointeurs bruts vers les films du genre spécifié.
/// \param genre			   Le genre des films à chercher.
/// \return                    Le vecteur de pointeurs des films du genre recherché. Vecteur vide si aucun film du genre.
std::vector<const Film*> GestionnaireFilms::getFilmsParGenre(Film::Genre genre) const
{
	auto iterateurVecteur = filtreGenreFilms_.find(genre);
	if (iterateurVecteur == filtreGenreFilms_.end())
	{
		return std::vector<const Film*>();
	}
	return iterateurVecteur->second;
}

/// Retourne un vecteur de pointeurs bruts vers les films du pays spécifié.
/// \param pays				   Le pays des films à chercher.
/// \return                    Le vecteur de pointeurs des films du pays recherché. Vecteur vide si aucun film du genre.
std::vector<const Film*> GestionnaireFilms::getFilmsParPays(Pays pays) const
{
	auto iterateurVecteur = filtrePaysFilms_.find(pays);
	if (iterateurVecteur == filtrePaysFilms_.end())
	{
		return std::vector<const Film*>();
	}
	return iterateurVecteur->second;
}

/// Retourne un vecteur de pointeurs bruts vers les films des années spécifiées.
/// \param anneeDebut		   L'année de début des films à chercher.
/// \param anneeFin			   L'année de fin des films à chercher.
/// \return                    Le vecteur de pointeurs des films des années recherchées. Vecteur vide si aucun film du genre.
std::vector<const Film*> GestionnaireFilms::getFilmsEntreAnnees(int anneeDebut, int anneeFin)
{
	std::vector<const Film*> vecteurAnnees;
	std::copy_if(films_.begin(), films_.end(), RawPointerBackInserter(vecteurAnnees), [&](const std::unique_ptr<Film>& ptrfilm) -> bool
		{
			return EstDansIntervalleDatesFilm(anneeDebut, anneeFin)(ptrfilm);
		});
	return vecteurAnnees;
}



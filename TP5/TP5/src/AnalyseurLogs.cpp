/// Analyseur de statistiques grâce aux logs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include "AnalyseurLogs.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Foncteurs.h"

/// Ajoute les lignes de log en ordre chronologique à partir d'un fichier de logs.
/// \param nomFichier               Le fichier à partir duquel lire les logs.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout le chargement s'est effectué avec succès, false sinon.
bool AnalyseurLogs::chargerDepuisFichier(const std::string& nomFichier,
                                         GestionnaireUtilisateurs& gestionnaireUtilisateurs,
                                         GestionnaireFilms& gestionnaireFilms)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        logs_.clear();
        vuesFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string timestamp;
            std::string idUtilisateur;
            std::string nomFilm;

            if (stream >> timestamp >> idUtilisateur >> std::quoted(nomFilm))
            {
                // TODO: Uncomment une fois que la fonction creerLigneLog est écrite
                creerLigneLog(timestamp, idUtilisateur, nomFilm, gestionnaireUtilisateurs, gestionnaireFilms);
            }
            else
            {
                std::cerr << "Erreur AnalyseurLogs: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur AnalyseurLogs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

/// Crée une ligne de log et l'ajoute au vecteur.
/// \param timestamp                La date du log.
/// \param idUtilisateur            L'id de l'utilisateur dont le log est associé.
/// \param nomFilm                  Le nom du film associé au log.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si la ligne a été ajoutée, false sinon.
bool AnalyseurLogs::creerLigneLog(const std::string& timestamp, 
                                  const std::string& idUtilisateur, 
                                  const std::string& nomFilm,
                                  GestionnaireUtilisateurs& gestionnaireUtilisateurs, 
                                  GestionnaireFilms& gestionnaireFilms)
{
    if (gestionnaireUtilisateurs.getUtilisateurParId(idUtilisateur) == nullptr ||
        gestionnaireFilms.getFilmParNom(nomFilm) == nullptr)
    {
        return false;
    }
    ajouterLigneLog({timestamp, gestionnaireUtilisateurs.getUtilisateurParId(idUtilisateur), gestionnaireFilms.getFilmParNom(nomFilm)});
    return true;
}

/// Ajoute une ligne de log au vecteur.
/// \param ligneLog                La ligne de log à ajouter.
void AnalyseurLogs::ajouterLigneLog(const LigneLog& ligneLog)
{
    ComparateurLog comparateur;
    logs_.insert(std::upper_bound(logs_.begin(), logs_.end(), ligneLog, comparateur), ligneLog);
    vuesFilms_[ligneLog.film]++;
}

/// Retourne le nombre de vues pour un film.
/// \param film                     Le film dont on veut savoir le nombre de vues.
/// \return                         Le nombre de vues pour ce film.
int AnalyseurLogs::getNombreVuesFilm(const Film* film) const
{
    std::unordered_map<const Film*, int>::const_iterator iterateurFilm = vuesFilms_.find(film);
    if (iterateurFilm != vuesFilms_.end())
    {
        return iterateurFilm->second;
    }
    return 0;
}

/// Cherche le film le plus populaire.
/// \return                         Un pointeur vers le film le plus populaire
const Film* AnalyseurLogs::getFilmPlusPopulaire() const
{
    ComparateurSecondElementPaire <const Film*, int> comparateur;
    if (logs_.size() == 0)
    {
        return nullptr;
    }
    return std::max_element(vuesFilms_.begin(), vuesFilms_.end(), comparateur)->first;
    return nullptr;
}

/// Cherche un certain nombre des films les plus populaires.
/// \param nombre                   Le nombre de films désirés.
/// \return                         Un vecteur de paires de films et de vues contenant les films les plus populaires
std::vector<std::pair<const Film*, int>> AnalyseurLogs::getNFilmsPlusPopulaires(std::size_t nombre) const
{
    //On copie les paires dans un vecteur pour utiliser la méthode sort
    std::vector<std::pair<const Film*, int>> filmsACopier = std::vector<std::pair<const Film*, int>>(vuesFilms_.begin(), vuesFilms_.end());

    //On trie les films du plus populaire au moins populaire
    std::sort(filmsACopier.begin(), filmsACopier.end(), [](const std::pair<const Film*, int>& paireA, const std::pair<const Film*, int>& paireB)
        {return paireA.second > paireB.second; });
    
    //On crée le vecteur des films populaires
    std::size_t grandeurVecteur = std::min(nombre, vuesFilms_.size());
    std::vector<std::pair<const Film*, int>> filmsPopulaires = std::vector<std::pair<const Film*, int>>();
    std::copy_n(filmsACopier.begin(), grandeurVecteur, std::back_inserter(filmsPopulaires));
    return filmsPopulaires;
}

/// Retourne le nombre de vues pour un utilisateur.
/// \param utilisateur              L'utilisateur dont on cherche le nombre de vues.
/// \return                         Le nombre de vues pour un cet utilisateur.
int AnalyseurLogs::getNombreVuesPourUtilisateur(const Utilisateur* utilisateur) const
{
    return std::count_if(logs_.begin(), logs_.end(), [&utilisateur](const LigneLog& ligneLog) 
        {return ligneLog.utilisateur->id == utilisateur->id; });
 
}

/// Crée un vecteur des films vus par l'utilisateur.
/// \param utilisateur              L'utilisateur dont on veut connaître les films vus.
/// \return                         Un vecteur contenant tous les films vus par l'utilisateur.
std::vector<const Film*> AnalyseurLogs::getFilmsVusParUtilisateur(const Utilisateur* utilisateur) const
{
   /* std::unordered_set<const Film*> filmsACopier;
    for (LigneLog ligneLog : logs_)
    {
        if (ligneLog.utilisateur->nom == utilisateur->nom)
        {
            filmsACopier.insert(ligneLog.film);
        }
    }*/
    return std::vector<const Film*>();// (filmsACopier.begin(), filmsACopier.end());
}

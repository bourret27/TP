/// Gestionnaire d'utilisateurs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

#include "GestionnaireUtilisateurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/// Affiche les informations des utilisateurs gérés par le gestionnaire d'utilisateurs à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des utilisateurs.
/// \param gestionnaireFilms    Le gestionnaire d'utilisateurs à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireUtilisateurs& gestionnaireUtilisateurs)
{
    outputStream << "Le gestionnaire d'utilisateurs contient " << gestionnaireUtilisateurs.getNombreUtilisateurs()
                 << " utilisateurs:\n";

    for (const auto& [idUtilisateur, utilisateur] : gestionnaireUtilisateurs.utilisateurs_)
    {
        outputStream << '\t' << utilisateur << '\n';
    }
    return outputStream;
}

/// Ajoute les utilisateurs à partir d'un fichier de données d'utilisateurs.
/// \param nomFichier   Le fichier à partir duquel lire les informations des utilisateurs.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireUtilisateurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        utilisateurs_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string id;
            std::string nom;
            int age;
            int pays;

            if (stream >> id >> std::quoted(nom) >> age >> pays)
            {
				ajouterUtilisateur(Utilisateur{id, nom, age, static_cast<Pays>(pays)});
            }
            else
            {
                std::cerr << "Erreur GestionnaireUtilisateurs: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur GestionnaireUtilisateurs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}


/// Ajoute un utilisateur au gestionnaire.
/// \param utilisateur         L'utilisateur à ajouter au gestionnaire.
/// \return                    Un booléen indiquant si l'utilisateur a été ajouté ou s'il était déjà présent.
bool GestionnaireUtilisateurs::ajouterUtilisateur(const Utilisateur& utilisateur)
{
	return utilisateurs_.emplace(utilisateur.id, utilisateur).second;
}

/// Supprime un utilisateur du gestionnaire.
/// \param utilisateur         L'utilisateur à supprimer du gestionnaire.
/// \return                    Un booléen indiquant si l'utilisateur a été supprimé ou s'il n'était déjà pas présent.
bool GestionnaireUtilisateurs::supprimerUtilisateur(const std::string& idUtilisateur)
{
	return utilisateurs_.erase(idUtilisateur) != 0;
}

/// Retourne le nombre d'utilisateurs dans le gestionnaire.
/// \return                    Le nombre d'utilisateurs dans le gestionnaire.
std::size_t GestionnaireUtilisateurs::getNombreUtilisateurs() const
{
	return utilisateurs_.size();
}

/// Retourne un pointeur pointant vers l'utilisateur selon l'id spécifié.
/// \param utilisateur         L'id de l'utilisateur à chercher.
/// \return                    Le pointeur vers l'utilisateur recherché. nullptr si pas trouvé.
const Utilisateur* GestionnaireUtilisateurs::getUtilisateurParId(const std::string& id) const
{
	std::unordered_map<std::string, Utilisateur>::const_iterator iterateurUtilisateur = utilisateurs_.find(id);
	if (iterateurUtilisateur == utilisateurs_.end())
	{
		return nullptr;
	}
	return &iterateurUtilisateur->second;
}
/*
 * Titre : AgrandirMatrice.h - Travail Pratique #4 - Programmation Orient�e
 * Objet Date : 27 F�vrier 2020 Auteur : Nabil Dabouz
 */

 /*
 * Classe qui définit un template pour agrandir une matrice par la methode du plus proche voisin.
 * \file   AgrandirMatrice.h
 * \author William Bourret et Philippe De Blois
 * \date   25 mars 2020
 * Créé le 25 mars 2020
 */

#ifndef AGRANDIR_MATRICE_H
#define AGRANDIR_MATRICE_H

#include "def.h"

template <class M> class AgrandirMatrice {
public:
  AgrandirMatrice();
  AgrandirMatrice(M *matrice);
  ~AgrandirMatrice() = default;
  Coordonnees trouverLePlusProcheVoisin(const unsigned int &rapport,
                                        size_t posY, size_t posX) const;
  void redimensionnerImage(const unsigned int &rapport);

private:
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> AgrandirMatrice<M>::AgrandirMatrice() : matrice_(nullptr) {
	// rien à faire dans le corps du constructeur
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
AgrandirMatrice<M>::AgrandirMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver le point le plus proche du point (posX, posY) dans la matrice
 * originale
 * @param rapport, le rapport du redimensionnement de l'image
 * @param posX, la colonne du point dans la nouvelle image
 * @param posY, la ligne du point dans la nouvelle image
 * @return coordonnées du point le plus proche
 */
template <class M>
Coordonnees
AgrandirMatrice<M>::trouverLePlusProcheVoisin(const unsigned int &rapport,
                                              size_t posY, size_t posX) const {
	// La division entiere s'occupe d'obtenir le bon chiffre (equivalent a la fonction floor)
	int voisinY = static_cast<int>(posY / rapport);
	int voisinX = static_cast<int>(posX / rapport);
  return {voisinX, voisinY};
}

/**
 * @brief redimensionne la matrice selon le rapport de grandeur specifie
 * @param rapport, le rapport du redimensionnement de l'image
 */
template <class M> void AgrandirMatrice<M>::redimensionnerImage(const unsigned int& rapport) {
    //On sauvegarde l'ancienne matrice
    std::unique_ptr<M> matriceOriginale = matrice_->clone();

    //On ajuste les dimension pour la nouvelle matrice
	std::size_t height = matrice_->getHeight();
	std::size_t width = matrice_->getWidth();
	matrice_->setHeight(height * rapport);
	matrice_->setWidth(width * rapport);

    //On agrandie la matrice
	for (int y = matrice_->getHeight() - 1; y >= 0; y--) {
		for (int x = matrice_->getWidth() - 1; x >= 0; x--) {
			// Obtenir les coordonnees du plus proche voisin
			Coordonnees coordsProcheVoisin = trouverLePlusProcheVoisin(rapport, y, x);

			// On ajoute l'element a la matrice agrandie en allant le chercher dans la matrice originale
			matrice_->ajouterElement((*matriceOriginale)(coordsProcheVoisin.y, coordsProcheVoisin.x), y, x);
		}
	}
}

#endif

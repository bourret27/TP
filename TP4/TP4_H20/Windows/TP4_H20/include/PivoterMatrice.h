/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M> class PivoterMatrice {
public:
  // Constructeurs
  PivoterMatrice();
  PivoterMatrice(M *matrice);
  // Destructeur
  ~PivoterMatrice() = default;
  void pivoterMatrice(Direction direction);

private:
  Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
  Coordonnees recupererCoordonnees(Coordonnees coords) const;
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice() : matrice_(nullptr) {
  // TO DO

}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M> inline Coordonnees PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
  // TO DO
    Coordonnees nouveauxCoords = {};
    nouveauxCoords.x = coords.x - matrice_->getWidth() / 2;
    nouveauxCoords.y = coords.y - matrice_->getHeight() / 2;
    return nouveauxCoords;
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M> inline Coordonnees PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
  // TO DO
    Coordonnees anciennesCoords = {};
    anciennesCoords.x = coords.x + matrice_->getWidth() / 2;
    anciennesCoords.y = coords.y + matrice_->getHeight() / 2;
    return anciennesCoords;
}

template <class M> inline void PivoterMatrice<M>::pivoterMatrice(Direction direction) {
    std::unique_ptr<M> matricePivotee = matrice_->clone();
    
    for (int y = 0; y < matricePivotee->getHeight(); ++y) {
        for (int x = 0; x < matricePivotee->getHeight(); ++x) {
            Coordonnees coordonnesActuels = changerCoordonneesCentreMatrice({ x, y });
            if (direction == Direction::Right) {
                coordonnesActuels.x = coordonnesActuels.y;
                coordonnesActuels.y = -coordonnesActuels.x;
            }
            else if (direction == Direction::Left) {
                coordonnesActuels.x = -coordonnesActuels.y;
                coordonnesActuels.y = coordonnesActuels.x;
            }
            coordonnesActuels = recupererCoordonnees(coordonnesActuels);
            matricePivotee->ajouterElement((*matrice_)(coordonnesActuels.y, coordonnesActuels.x), y, x);
        }
    }


}

#endif

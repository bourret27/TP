/*
 * Titre : PivoterMatrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

 /*
  * Classe qui définit un template pour pivoter une matrice.
  * \file   PivoterMatrice.h
  * \author William Bourret et Philippe De Blois
  * \date   25 mars 2020
  * Créé le 25 mars 2020
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
    // rien à faire dans le corps du constructeur
}
/**
 * @brief constructeur par paramètre de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {}
/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 * @return les coordonnées par rapport au centre de la matrice
 */
template <class M> inline Coordonnees PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
    Coordonnees nouveauxCoords = {};
    nouveauxCoords.x = coords.x - matrice_->getWidth() / 2;
    nouveauxCoords.y = coords.y - matrice_->getHeight() / 2;
    return nouveauxCoords;
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 * @return les coordonnées par rapport au premier élément de la matrice
 */
template <class M> inline Coordonnees PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
    Coordonnees anciennesCoords = {};
    anciennesCoords.x = coords.x + matrice_->getWidth() / 2;
    anciennesCoords.y = coords.y + matrice_->getHeight() / 2;
    return anciennesCoords;
}

/**
 * @brief pivoter une matrice
 * @param la direction dans laquelle pivoter
 */
template <class M> inline void PivoterMatrice<M>::pivoterMatrice(Direction direction) {
    //On sauvegarde l'ancienne matrice
    std::unique_ptr<M> matriceOriginale = matrice_->clone();

    //On calcule le coefficient de rotation
    int sensRotation = (int)Direction::last_ * (int)direction + (int)Direction::first_;

    //On pivote la matrice
    for (int y = matrice_->getHeight() - 1; y >= 0; --y) {
        for (int x = matrice_->getWidth() - 1; x >= 0; --x) {
            //On change de système de coordonnées
            Coordonnees coordonnesCentre = changerCoordonneesCentreMatrice({ x,y });

            //On calcule les nouveaux points selon la rotation
            Coordonnees coordonnesPivotees = {};
            coordonnesPivotees.x = sensRotation * -coordonnesCentre.y;
            coordonnesPivotees.y = sensRotation * coordonnesCentre.x;

            //On retourne dans l'ancien système de coordonnées et on copie l'élément de la matrice originale dans la matrice pivotée 
            Coordonnees coordonnesBase = recupererCoordonnees(coordonnesPivotees);
            matrice_->ajouterElement((*matriceOriginale)(coordonnesBase.y, coordonnesBase.x), y, x);

        }
    }
    
    


}

#endif

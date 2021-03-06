﻿/*
 * Titre : Matrice.h - Travail Pratique #4 - Programmation Orient�e Objet
 * Date : 27 F�vrier 2020
 * Auteur : Nabil Dabouz
 */

 /*
  * Classe qui définit un template pour une matrice d'elements generiques.
  * \file   Matrice.h
  * \author William Bourret et Philippe De Blois
  * \date   25 mars 2020
  * Créé le 25 mars 2020
  */

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template <typename T> class Matrice {

public:
  Matrice();
  // Destructeur
  ~Matrice() = default;
  T operator()(const size_t &posY, const size_t &posX) const;
  // Lecture du fichier
  bool chargerDepuisFichier(const std::string &nomFichier);
  bool lireElement(const std::string &elementFichier, const size_t &posY,
                   const size_t &posX);
  // Remplir un matrice
  bool ajouterElement(T element, const size_t &posY, const size_t &posX);
  // Faire une copie
  std::unique_ptr<Matrice<T>> clone() const;
  // Setters
  void setHeight(size_t height);
  void setWidth(size_t width);
  // Getters
  size_t getHeight() const;
  size_t getWidth() const;

private:
  std::vector<std::vector<T>> elements_;
  size_t height_;
  size_t width_;
};

namespace {
static constexpr int CAPACITE_MATRICE = 100;
}

/**
 * @brief constructeur par défaut de la classe
 */
template <typename T> inline Matrice<T>::Matrice() : 
    elements_(std::vector<std::vector<T>>(CAPACITE_MATRICE)), 
    height_(0),
    width_(0)
{
  // TO DO
    for (unsigned i = 0; i < elements_.size(); ++i)
        elements_[i] = std::vector<T>(CAPACITE_MATRICE);
}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getHeight() const {
  return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getWidth() const {
  return width_;
}

/**
 * @brief retourne le nombre de colonnes de la matrice
 * @param height, le nombre de lignes voulu dans la matrice
 */
template <typename T> inline void Matrice<T>::setHeight(size_t height) {
    //if (height >= 0)
        height_ = height;
}

/**
 * @brief retourne le nombre de colonnes de la matrice
 * @param width, le nombre de colonnes voulu dans la matrice
 */
template <typename T> inline void Matrice<T>::setWidth(size_t width) {
    //if (width >= 0)
        width_ = width;
}
/**
* @brief retourne l'élément aux coordonnées indiquées
* @param posY, la position en y
* @param posX, la position en x
* @return l'élément situé aux coordonnées indiquées 
*/
template <typename T> inline T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const {
    if (posY > height_ || posX > width_)
        return T();
    else
        return elements_[posY][posX];
}

/**
* @brief lit une matrice à partir d'un fichier
* @param nomFichier, le nom du fichier à lire
* @return un booléen indiquant la réussite de la lecture
*/
template <typename T> inline bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier) {
    const std::string CARACTERE_CHANGEMENT_LIGNE = "L";
    std::ifstream fichierLecture(nomFichier);
    std::string element;
    if (fichierLecture)
    {
        while (!ws(fichierLecture).eof())
        {
            std::getline(fichierLecture, element);
            if (element == CARACTERE_CHANGEMENT_LIGNE) {
                height_++;
                width_ = 0;
            }                
            else
                if (lireElement(element, height_ - 1, width_++) == false)
                    return false;
        }
        return true;
    }
    return false;
}

/**
* @brief lit un élément à partir du chaîne lue dans le fichier précédent
* @param elementFichier, la chaîne contenant l'élément à lire
* @param posY, la position en y où on ajoute l'élément
* @param posX, la position en x où on ajoute l'élément
* @return un booléen indiquant la réussite de la lecture
*/
template <typename T> inline bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX) {
    std::istringstream stream(elementFichier);
    T elementAAjouter;
    if (stream >> elementAAjouter)
    {
        return ajouterElement(elementAAjouter, posY, posX);
    }
    return false;
}

/**
* @brief ajoute un élément dans la matrice
* @param element, l'élément à ajouter
* @param posY, la position en y où on ajoute l'élément
* @param posX, la position en x où on ajoute l'élément
* @return un booléen indiquant la réussite de l'ajout
*/
template <typename T> inline bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX) {
	if (!(posY > height_ || posX > width_))
	{
		elements_[posY][posX] = element;
		return true;
	}
    return false;
        
}

/**
* @brief retourne une copie de la matrice
* @return un pointeur intelligent vers la copie de la matrice
*/
template <typename T> inline std::unique_ptr<Matrice<T>> Matrice<T>::clone() const {
	std::unique_ptr<Matrice<T>> copie = std::make_unique<Matrice<T>>(Matrice<T>());
	copie->setHeight(getHeight());
	copie->setWidth(getWidth());
	for (std::size_t y = 0; y < copie->getHeight(); y++)
	{
		for (std::size_t x = 0; x < copie->getWidth(); x++)
		{
			copie->ajouterElement(elements_[y][x], y, x);
		}
	}
    return copie;
}
#endif

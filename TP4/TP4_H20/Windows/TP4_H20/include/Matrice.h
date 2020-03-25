/*
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

template <typename T> inline void Matrice<T>::setHeight(size_t height) {
    if (height >= 0)
        height_ = height;
}

template <typename T> inline void Matrice<T>::setWidth(size_t width) {
    if (width >= 0)
        width_ = width;
}

template <typename T> inline T Matrice<T>::operator()(const size_t& posY, const size_t& posX) const {
    if (posY > height_ || posX > width_ || posY < 0 || posX < 0)
        return T();
    else
        return elements_[posY][posX];
}

template <typename T> inline bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier) {
    const char CARACTERE_CHANGEMENT_LIGNE = 'L';
    std::ifstream fichierLecture(nomFichier);
    std::string element;
    if (fichierLecture)
    {
        while (!ws(fichierLecture).eof())
        {
            std::getline(fichierLecture, element);
            if (element == CARACTERE_CHANGEMENT_LIGNE)
            {
                height_++;
                width_ = 0;
            }
            else
                if (lireElement(element, height_, width_++) == false)
                    return false;
        }
        return true;
    }
    return false;
}

template <typename T> inline bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX) {
    std::istringstream stream(elementFichier);
    T elementAAjouter;
    if (stream >> elementFichier)
    {
        return ajouterElement(elementAAjouter, posY, posX);
    }
    return false;
}

template <typename T> inline bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX) {
    if (*(this)(posY, posX) != T())
    {
        elements[posY][posX] = element;
        return true;
    }
    return false;
        
}

template <typename T> inline std::unique_ptr<Matrice<T>> Matrice<T>::clone() const {
    std::unique_ptr<Matrice<T>> copie = make_unique<Matrice<T>>(*this);
    return copie;
}
#endif

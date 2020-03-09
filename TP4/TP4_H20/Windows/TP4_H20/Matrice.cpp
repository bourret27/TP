#include "Matrice.h"

template<typename T>
Matrice<T>::Matrice() : elements_(std::vector<std::vector<T>>(CAPACITE_MATRICE)), width_(0), height_(0)
{
	for (unsigned i = 0; i < elements_.size(); ++i)
	{
		elements_[i] = std::vector<T>(CAPACITE_MATRICE);
	}
}

template<typename T>
T Matrice<T>::operator() (const size_t& posY, const size_t& posX) const
{
	if (posX > width_ || posy > height_ || posX < 0 || posY < 0)
		return T();
	return elements_[posY][posX];
}

//A revoir
template<typename T>
bool Matrice<T>::chargerDepuisFichier(const std::string& nomFichier)
{
	const char CARACTERE_ARRET = 'L';
	std::ifstream fichier(nomFichier);
	std::string element;
	if (fichier)
	{
		while (std::getline(fichier, element, CARACTERE_ARRET))
		{
			if (lireElement(element, height_++, width_++) == false)
			{
				return false;
			}
		}
	}
	return false;
}

//A revoir
template<typename T>
bool Matrice<T>::lireElement(const std::string& elementFichier, const size_t& posY, const size_t& posX)
{
	T elementAAjouter
	if (elementAAjouter >> elementFichier)
	{
		return ajouterElement(elementAAjouter, posY, posX);
	}
	return false;
}

template<typename T>
std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
	std::unique_ptr<Matrice<T>> clone = std::make_unique(*this);
	return clone;
}

template<typename T>
bool Matrice<T>::ajouterElement(T element, const size_t& posY, const size_t& posX)
{
	if (*this(posY, posX) != T())
	{
		elements_[posY][posX] = element;
		return true;
	}
	return false;
}

template<typename T>
void Matrice<T>::setHeight(size_t height)
{
	if (height >= 0)
		height_ = height;
}

template<typename T>
void Matrice<T>::setWidth(size_t width)
{
	if (width >= 0)
		width_ = width;
}

template<typename T>
size_t Matrice<T>::getHeight() const
{
	return height_;
}

template<typename T>
size_t Matrice<T>::getWidth() const
{
	return width_;
}
#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(rouge), vert_(vert), bleu_(bleu) {}

void Pixel::operator=(const Pixel &pixel) {
	setRouge(pixel.getRouge());
	setVert(pixel.getVert());
	setBleu(pixel.getBleu());
}

void Pixel::setRouge(int rouge) {
	// On clamp la borne supérieure
	rouge = rouge > 255 ? 255 : rouge;
	// On clamp la borne inférieure
	rouge = rouge < 0 ? 0 : rouge;
	rouge_ = static_cast<uint8_t>(rouge);
}

void Pixel::setVert(int vert) {
	// On clamp la borne supérieure
	vert = vert > 255 ? 255 : vert;
	// On clamp la borne inférieure
	vert = vert < 0 ? 0 : vert;
	vert_ = static_cast<uint8_t>(vert);
}

void Pixel::setBleu(int bleu) {
	// On clamp la borne supérieure
	bleu = bleu > 255 ? 255 : bleu;
	// On clamp la borne inférieure
	bleu = bleu < 0 ? 0 : bleu;
	bleu_ = static_cast<uint8_t>(bleu);
}
/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }
/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }
/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }

std::ostream &operator<<(std::ostream &os, Pixel pixel) {
	// On copie les flags afin de pouvoir les retablir apres l'execution de la methode 
	int flagsPrecedents = os.flags();
	// On modifie les flags pour obtenir l'affichage desire
	os << std::hex << std::setw(3) << std::setfill(' ') << std::left << std::uppercase;
	// On affiche le pixel
	os << '#' << pixel.getRouge() << pixel.getVert() << pixel.getBleu();
	// On remet les flags comme avant
	os.flags(flagsPrecedents);
	return os;
}

std::istream &operator>>(std::istream &is, Pixel &pixel) {
	int rouge = 0, vert = 0, bleu = 0;
	is >> rouge >> vert >> bleu;
	pixel.setRouge(rouge);
	pixel.setVert(vert);
	pixel.setBleu(bleu);
	return is;
}
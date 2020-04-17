/// Foncteurs en tous genres.
/// \author William Bourret et Philippe De Blois
/// \date 2020-04-16

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <string>
#include "Film.h"
#include "LigneLog.h"

class EstDansIntervalleDatesFilm {
public:
	EstDansIntervalleDatesFilm(int anneeInferieure, int anneeSuperieure) : anneeInferieure_(anneeInferieure), anneeSuperieure_(anneeSuperieure) {}
	/// Retourne un booléen indiquant si le film est sorti durant les années spécifiées dans le foncteur.
	/// \param film		   Le film à tester.
	/// \return            Le booléen indiquant si le film est sorti durant les années spécifiées dans le foncteur.
	bool operator()(const std::unique_ptr<Film>& film) 
	{
		return film->annee >= anneeInferieure_ && film->annee <= anneeSuperieure_;
	}

private:
	int anneeInferieure_;
	int anneeSuperieure_;

};

class ComparateurLog {
public:
	/// Compare deux lignes de log et retourne un booléen indiquant si la première ligne est strictement plus ancienne que la deuxième.
	/// \param logA		   La première ligne de log.
	/// \param logB		   La deuxième ligne de log.
	/// \return            Le booléen indiquant si la première ligne est strictement plus ancienne que la deuxième.
	bool operator()(const LigneLog& logA, const LigneLog& logB) 
	{
		return logA.timestamp < logB.timestamp;
	}

};

template<typename T1, typename T2>
class ComparateurSecondElementPaire {
public:
	/// Compare deux paires de types et indique si le second élément de la paire 1 est strictement plus petit que le second élément de la paire 2.
	/// \param pairA		   La première paire.
	/// \param pairB		   La deuxième paire.
	/// \return                Le booléen indiquant si le second élément de la paire 1 est strictement plus petit que le second élément de la paire 2.
	bool operator()(const std::pair<T1, T2>& pairA, const std::pair<T1, T2>& pairB)
	{
		return pairA.second < pairB.second;
	}

};


#endif // FONCTEURS_H
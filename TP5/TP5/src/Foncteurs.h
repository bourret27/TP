/// Foncteurs en tous genres.
/// \author William Bourret et Philippe De Blois
/// \date 2020-04-16

#ifndef FONCTEURS_H
#define FONCTEURS_H

// TODO : Mettre les includes nécéssaires
#include <memory>
#include <string>
#include "Film.h"
#include "LigneLog.h"

class EstDansIntervalleDatesFilm {
public:
	EstDansIntervalleDatesFilm(int anneeInferieure, int anneeSuperieure) : anneeInferieure_(anneeInferieure), anneeSuperieure_(anneeSuperieure) {}
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
	bool operator()(const LigneLog& logA, const LigneLog& logB) 
	{
		return logA.timestamp < logB.timestamp;
	}

};

template<typename T1, typename T2>
class ComparateurSecondElementPaire {
public:
	bool operator()(const std::pair<T1, T2>& pairA, const std::pair<T1, T2>& pairB)
	{
		return pairA.second < pairB.second;
	}

};


#endif // FONCTEURS_H
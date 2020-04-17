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
	/// Retourne un bool�en indiquant si le film est sorti durant les ann�es sp�cifi�es dans le foncteur.
	/// \param film		   Le film � tester.
	/// \return            Le bool�en indiquant si le film est sorti durant les ann�es sp�cifi�es dans le foncteur.
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
	/// Compare deux lignes de log et retourne un bool�en indiquant si la premi�re ligne est strictement plus ancienne que la deuxi�me.
	/// \param logA		   La premi�re ligne de log.
	/// \param logB		   La deuxi�me ligne de log.
	/// \return            Le bool�en indiquant si la premi�re ligne est strictement plus ancienne que la deuxi�me.
	bool operator()(const LigneLog& logA, const LigneLog& logB) 
	{
		return logA.timestamp < logB.timestamp;
	}

};

template<typename T1, typename T2>
class ComparateurSecondElementPaire {
public:
	/// Compare deux paires de types et indique si le second �l�ment de la paire 1 est strictement plus petit que le second �l�ment de la paire 2.
	/// \param pairA		   La premi�re paire.
	/// \param pairB		   La deuxi�me paire.
	/// \return                Le bool�en indiquant si le second �l�ment de la paire 1 est strictement plus petit que le second �l�ment de la paire 2.
	bool operator()(const std::pair<T1, T2>& pairA, const std::pair<T1, T2>& pairB)
	{
		return pairA.second < pairB.second;
	}

};


#endif // FONCTEURS_H
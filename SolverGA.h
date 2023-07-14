#pragma once
#include "KnapsackProblem.h"
#include "gatypes.h"
#include "Population.h"
#include "Chromosome.h"
class SolverGA
{

	KnapsackProblem problem;

	size_t popSize;

	size_t survivorSize;
	size_t mutantSize;
	size_t crossoverSize;

	size_t chromosomeSize;
	

public:
	Population population;
	SolverGA(KnapsackProblem problem, size_t popSize, double survivorPart);
	void mutate_reverse(Chromosome& chromosome);
	void mutate_flip(Chromosome& chromosome);
	void crossover_single(Chromosome& chromosome1, Chromosome& chromosome2);
	void crossover_double(Chromosome& chromosome1, Chromosome& chromosome2);
	score_t solver_iteration();
	Chromosome bestResult();
};


#pragma once
#include "gatypes.h"
#include "Chromosome.h"
#include <vector>

class Population
{
public:
	std::vector<Chromosome> solutions;
	Population(size_t popSize, size_t chromosomeSize);
};


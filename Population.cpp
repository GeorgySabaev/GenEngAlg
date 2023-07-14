#include "Population.h"

Population::Population(size_t popSize, size_t chromosomeSize)
{
	solutions = std::vector<Chromosome>(popSize, Chromosome(chromosomeSize));
	for (auto &c : solutions)
	{
		for (auto i : c.genes)
		{
			if (rand() % 2) {
				i.flip();
			}
		}
	}
}

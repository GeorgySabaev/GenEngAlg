#include "SolverGA.h"
#include <algorithm>
#include "RandomUtils.h"

SolverGA::SolverGA(KnapsackProblem problem, size_t popSize, double survivorPart) :
	population(popSize, problem.getSize()),
	popSize(popSize),
	problem(problem),
	survivorSize(popSize* survivorPart),
	chromosomeSize(problem.getSize())
{
	mutantSize = (popSize - survivorSize) / 2;
	crossoverSize = popSize - survivorSize - mutantSize;
	if (crossoverSize % 2) {
		--crossoverSize;
		++mutantSize;
	}
}

void SolverGA::mutate_reverse(Chromosome& chromosome) {
	size_t reverse_end = rand() % chromosomeSize;
	size_t reverse_begin = (rand() % (chromosomeSize - 1) + reverse_end) % chromosomeSize;
	if (reverse_begin > reverse_end) {
		std::swap(reverse_end, reverse_begin);
	}
	while (reverse_begin < reverse_end) {
		std::vector<bool>::swap(chromosome.genes[reverse_end--], chromosome.genes[reverse_begin++]);
	}
}
void SolverGA::mutate_flip(Chromosome& chromosome) {
	size_t position = rand() % chromosomeSize;
	chromosome.genes[position].flip();
}

void SolverGA::crossover_single(Chromosome& chromosome1, Chromosome& chromosome2) {
	size_t position = rand() % chromosomeSize;
	for (size_t i = position; i < chromosomeSize; i++)
	{
		std::vector<bool>::swap(chromosome1.genes[i], chromosome2.genes[i]);
	}
}

void SolverGA::crossover_double(Chromosome& chromosome1, Chromosome& chromosome2) {
	size_t cross_end = rand() % chromosomeSize;
	size_t cross_begin = (rand() % (chromosomeSize - 1) + cross_end) % chromosomeSize;
	if (cross_begin > cross_end) {
		std::swap(cross_end, cross_begin);
	}
	for (size_t i = cross_begin; i <= cross_end; i++)
	{
		std::vector<bool>::swap(chromosome1.genes[i], chromosome2.genes[i]);
	}
}


score_t SolverGA::solver_iteration()
{
	std::sort(population.solutions.begin(), population.solutions.end(), [this](Chromosome a, Chromosome b) {return problem.assess(a) > problem.assess(b); });
	population.solutions.resize(survivorSize);
	auto mutStart = population.solutions.size();
	std::sample(population.solutions.begin(), population.solutions.begin() + survivorSize, std::back_inserter(population.solutions), mutantSize,
		randenginefixed);
	for (auto i = population.solutions.begin() + mutStart; i < population.solutions.end(); i += 2)
	{
		if (rand() % 2) {
			mutate_reverse(*i);
		}
		else {
			mutate_flip(*i);
		}
	}
	auto crossStart = population.solutions.size();
	std::sample(population.solutions.begin(), population.solutions.begin() + survivorSize, std::back_inserter(population.solutions), crossoverSize,
		randenginefixed);
	for (auto i = population.solutions.begin() + crossStart; i < population.solutions.end(); i += 2)
	{
		if (rand() % 2) {
			crossover_double(*i, *(i + 1));
		}
		else {
			crossover_single(*i, *(i + 1));
		}
	}
	return problem.assess(population.solutions.front());
}

Chromosome SolverGA::bestResult()
{
	return population.solutions.front();
}

#include <iostream>
#include <sstream>
#include <fstream>
#include "Solvers.h"
#include "RandomUtils.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	os << "[";
	for (int i = 0; i < v.size(); ++i) {
		os << v[i];
		if (i != v.size() - 1)
			os << ", ";
	}
	os << "]";
	return os;
}

void printCSV(std::string path, std::vector<std::vector<score_t>>& table) {
	std::ofstream out;
	out.open(path);
	for (auto row : table)
	{
		out << row[0];
		for (size_t i = 1; i < row.size(); i++)
		{
			out << "," << row[i];
		}
		out << std::endl;
	}
	out.close();
}

template<class T>
score_t benchmarkSolver(T& solver, KnapsackProblem& problem) {
	score_t best = solver.solver_iteration();
	if (best != problem.assess(solver.bestResult())) {
		throw std::runtime_error("Incorrect score.");
	}
	return best;
}

void blockSmall(int n) {
	// 100 base 150 extended
	// items 0-10 linear
	// intervals from 50 to 1000
	std::vector<std::vector<score_t>> table;


}

std::pair<std::vector<std::vector<score_t>>, std::vector<std::vector<score_t>>> blockBase(
	std::string name, size_t attempt, 
	size_t iterations, size_t itemSize, int minItem, int maxItem, int minCapacity, int stepCapacity, int maxCapacity, int popSize, int popExtSize) {

	std::uniform_int_distribution<score_t> dist{ minItem, maxItem };
	auto gen = [&dist]() {
		return dist(randenginefixed);
	};
	std::vector<std::vector<score_t>> tableGASmall;
	std::vector<std::vector<score_t>> tableGAE;
	std::vector<std::vector<score_t>> tableGABig;

	std::string nameGASmall;
	std::stringstream ssNameGASmall;
	ssNameGASmall << name << "_GA_" << popSize << "_" << attempt;
	ssNameGASmall >> nameGASmall;
	std::ofstream streamGAS(nameGASmall);

	std::string nameGABig;
	std::stringstream ssNameGABig;
	ssNameGABig << name << "_GA_" << popExtSize << "_" << attempt;
	ssNameGABig >> nameGABig;

	std::string nameGAE;
	std::stringstream ssNameGAE;
	ssNameGAE << name << "_GAE_" << popSize << "_" << popExtSize << "_" << attempt;
	ssNameGAE >> nameGAE;

	for (size_t j = minCapacity; j < maxCapacity; j += stepCapacity) {
		std::vector<score_t> scores(itemSize);
		std::generate(scores.begin(), scores.end(), gen);
		KnapsackProblem problem(scores, j);
		SolverGA solverGASmall = SolverGA(problem, popSize, 0.6);
		SolverGA solverGABig = SolverGA(problem, popExtSize, 0.6);
		SolverGAE solverGAE = SolverGAE(problem, popSize, popExtSize, 0.6, 0.4, 1, 1, 1, 1, 1);

		tableGABig.emplace_back(iterations + 1);
		tableGABig.back()[0] = j;
		/*for (size_t i = 1; i <= iterations; i++) {
			tableGABig.back()[i] = solverGAB.
		}*/
	}
	return {};
}

int main()
{
	std::uniform_int_distribution<score_t> dist{ 1, 52 };
	auto gen = [&dist]() {
		return dist(randenginefixed);
	};
	std::vector<score_t> scores(100);
	std::generate(scores.begin(), scores.end(), gen);
	KnapsackProblem problem(scores, 10000);
	SolverGA solverGA = Solvers::getSolverGAbasic(problem);
	SolverGAE solverGAE = Solvers::getSolverGAEbasic(problem);
	std::cout << "iter#\tGA\tGEA" << std::endl;
	for (size_t i = 0; i < 20; i++)
	{
		std::cout << i + 1 << "\t" << benchmarkSolver(solverGA, problem) << "\t" << benchmarkSolver(solverGAE, problem) << std::endl;
	}
}
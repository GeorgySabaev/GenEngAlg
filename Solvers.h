#pragma once
#include "SolverGA.h"
#include "SolverGAE.h"
class Solvers
{
public:
	static SolverGA getSolverGAbasic(KnapsackProblem problem);
	static SolverGAE getSolverGAEbasic(KnapsackProblem problem);
	static SolverGAE getSolverGA(KnapsackProblem problem);
	static SolverGAE getSolverGAE1(KnapsackProblem problem);
	static SolverGAE getSolverGAE2(KnapsackProblem problem);
	static SolverGAE getSolverGAE3(KnapsackProblem problem);
	static SolverGAE getSolverGAE(KnapsackProblem problem);
};


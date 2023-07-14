#include "Solvers.h"

SolverGA Solvers::getSolverGAbasic(KnapsackProblem problem)
{
    return SolverGA(problem, 200, 0.5);
}

SolverGAE Solvers::getSolverGAEbasic(KnapsackProblem problem)
{
    return SolverGAE(problem, 200, 300, 0.6, 0.3, 1, 1, 1, 1, 1);
}

SolverGAE Solvers::getSolverGA(KnapsackProblem problem)
{
    return SolverGAE(problem, 200, 300, 0.6, 0.3, 1, 1, 0, 0, 0);
}

SolverGAE Solvers::getSolverGAE1(KnapsackProblem problem)
{
    return SolverGAE(problem, 200, 300, 0.6, 0.3, 1, 1, 1, 0, 0);
}
SolverGAE Solvers::getSolverGAE2(KnapsackProblem problem)
{
    return SolverGAE(problem, 200, 300, 0.6, 0.3, 1, 1, 0, 1, 0);
}
SolverGAE Solvers::getSolverGAE3(KnapsackProblem problem)
{
    return SolverGAE(problem, 200, 300, 0.6, 0.3, 1, 1, 0, 0, 1);
}

SolverGAE Solvers::getSolverGAE(KnapsackProblem problem)
{
    return SolverGAE(problem, 200, 300, 0.6, 0.3, 1, 1, 1, 1, 1);
}



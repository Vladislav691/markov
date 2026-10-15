#include "../Project1/MyForm.h"

int HeaderCompileCheck()
{
    PolynomialSolver::Polynomial polynomial({1, -2});
    PolynomialSolver::LinearEquation solver;
    PolynomialSolver::Solution result = solver.Solve(polynomial);
    return static_cast<int>(result.roots.size());
}

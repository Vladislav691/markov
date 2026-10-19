#pragma once

#include <cmath>

#include "Polynomial.h"

namespace PolynomialSolver
{
    using namespace std;

    constexpr double VerificationTolerance = 1e-8;

    enum class SolutionKind
    {
        Finite,
        None,
        Infinite
    };

    struct Solution
    {
        SolutionKind kind = SolutionKind::Finite;
        vector<Complex> roots;
        bool verified = false;
    };

    class EquationSolver
    {
    public:
        virtual ~EquationSolver() = default;
        virtual Solution Solve(const Polynomial& polynomial) const = 0;
    };

    inline void VerifySolution(const Polynomial& polynomial, Solution& solution)
    {
        solution.verified = true;

        for (Complex root : solution.roots)
        {
            if (!isfinite(root.real()) || !isfinite(root.imag()))
            {
                throw gcnew System::OverflowException(L"Вычисленный корень вышел за диапазон double.");
            }

            double residual = polynomial.RelativeResidual(root);

            if (residual > VerificationTolerance)
            {
                solution.verified = false;
            }
        }
    }
}

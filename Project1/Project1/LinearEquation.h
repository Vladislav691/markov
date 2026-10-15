#pragma once

#include <cmath>

#include "EquationSolver.h"

namespace PolynomialSolver
{
    using namespace std;

    class LinearEquation final : public EquationSolver
    {
    public:
        Solution Solve(const Polynomial& polynomial) const override
        {
            if (polynomial.Degree() != 1)
            {
                throw gcnew System::ArgumentException(L"Ожидается линейное уравнение.");
            }

            double a = polynomial.Coefficients()[0];
            double b = polynomial.Coefficients()[1];
            Solution result;

            if (a == 0)
            {
                if (b == 0)
                {
                    result.kind = SolutionKind::Infinite;
                }
                else
                {
                    result.kind = SolutionKind::None;
                }
            }
            else
            {
                double x = -b / a;
                result.roots.push_back(x);
            }

            return result;
        }
    };
}

#pragma once

#include <cmath>

#include "CubeEquation.h"
#include "EquationSolver.h"
#include "QuadraticEquation.h"

namespace PolynomialSolver
{
    using namespace std;

    class QuarticEquation final : public EquationSolver
    {
    public:
        Solution Solve(const Polynomial& polynomial) const override
        {
            if (polynomial.Degree() != 4)
            {
                throw gcnew System::ArgumentException(L"Ожидается уравнение четвёртой степени.");
            }

            double a = polynomial.Coefficients()[0];
            double b = polynomial.Coefficients()[1];
            double c = polynomial.Coefficients()[2];
            double d = polynomial.Coefficients()[3];
            double e = polynomial.Coefficients()[4];

            double A = b / a;
            double B = c / a;
            double C = d / a;
            double E = e / a;

            double p = B - 3 * A * A / 8;
            double q = A * A * A / 8 - A * B / 2 + C;
            double r = -3 * A * A * A * A / 256 + A * A * B / 16 - A * C / 4 + E;

            if (!isfinite(p) || !isfinite(q) || !isfinite(r))
            {
                throw gcnew System::OverflowException(L"Переполнение при вычислении по методу Феррари.");
            }

            double shift = A / 4;
            Solution result;

            if (q == 0)
            {
                Polynomial equation({1, p, r});
                QuadraticEquation solver;
                Solution squared = solver.Solve(equation);

                Complex y1 = sqrt(squared.roots[0]);
                Complex y2 = sqrt(squared.roots[1]);

                Complex x1 = y1 - shift;
                Complex x2 = -y1 - shift;
                Complex x3 = y2 - shift;
                Complex x4 = -y2 - shift;

                result.roots.push_back(x1);
                result.roots.push_back(x2);
                result.roots.push_back(x3);
                result.roots.push_back(x4);
            }
            else
            {
                Polynomial equation({1, 2 * p, p * p - 4 * r, -q * q});
                CubeEquation solver;
                Solution resolvent = solver.Solve(equation);

                Complex z = resolvent.roots[0];

                for (Complex root : resolvent.roots)
                {
                    if (abs(root) > abs(z))
                    {
                        z = root;
                    }
                }

                Complex s = sqrt(z);

                if (abs(s) == 0)
                {
                    throw gcnew System::InvalidOperationException(
                        L"Не удалось вычислить резольвенту Феррари.");
                }

                Complex t = (p + z - q / s) / 2.0;
                Complex u = (p + z + q / s) / 2.0;
                Complex first = sqrt(z - 4.0 * t);
                Complex second = sqrt(z - 4.0 * u);

                Complex x1 = (-s + first) / 2.0 - shift;
                Complex x2 = (-s - first) / 2.0 - shift;
                Complex x3 = (s + second) / 2.0 - shift;
                Complex x4 = (s - second) / 2.0 - shift;

                result.roots.push_back(x1);
                result.roots.push_back(x2);
                result.roots.push_back(x3);
                result.roots.push_back(x4);
            }

            return result;
        }
    };
}

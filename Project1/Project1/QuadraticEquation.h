#pragma once

#include <cmath>

#include "EquationSolver.h"

namespace PolynomialSolver
{
    using namespace std;

    class QuadraticEquation final : public EquationSolver
    {
    public:
        Solution Solve(const Polynomial& polynomial) const override
        {
            if (polynomial.Degree() != 2)
            {
                throw gcnew System::ArgumentException(L"Ожидается квадратное уравнение.");
            }

            double a = polynomial.Coefficients()[0];
            double b = polynomial.Coefficients()[1];
            double c = polynomial.Coefficients()[2];
            Solution result;

            double scale = abs(a);

            if (abs(b) > scale)
            {
                scale = abs(b);
            }

            if (abs(c) > scale)
            {
                scale = abs(c);
            }

            a = a / scale;
            b = b / scale;
            c = c / scale;

            double D = b * b - 4 * a * c;

            if (D > 0)
            {
                double x1;

                if (b >= 0)
                {
                    x1 = (-b - sqrt(D)) / (2 * a);
                }
                else
                {
                    x1 = (-b + sqrt(D)) / (2 * a);
                }

                double x2 = c / (a * x1);
                result.roots.push_back(x1);
                result.roots.push_back(x2);
            }
            else if (D == 0)
            {
                double x = -b / (2 * a);
                result.roots.push_back(x);
                result.roots.push_back(x);
            }
            else
            {
                double realPart = -b / (2 * a);
                double imaginaryPart = sqrt(-D) / (2 * abs(a));

                Complex x1(realPart, imaginaryPart);
                Complex x2(realPart, -imaginaryPart);

                result.roots.push_back(x1);
                result.roots.push_back(x2);
            }

            return result;
        }
    };
}

#pragma once

#include <cmath>

#include "EquationSolver.h"

namespace PolynomialSolver
{
    using namespace std;

    class CubeEquation final : public EquationSolver
    {
    public:
        Solution Solve(const Polynomial& polynomial) const override
        {
            if (polynomial.Degree() != 3)
            {
                throw gcnew System::ArgumentException(L"Ожидается кубическое уравнение.");
            }

            double a = polynomial.Coefficients()[0];
            double b = polynomial.Coefficients()[1];
            double c = polynomial.Coefficients()[2];
            double d = polynomial.Coefficients()[3];

            double A = b / a;
            double B = c / a;
            double C = d / a;

            double p = B - A * A / 3;
            double q = 2 * A * A * A / 27 - A * B / 3 + C;
            double D = q * q / 4 + p * p * p / 27;

            if (!isfinite(D))
            {
                throw gcnew System::OverflowException(L"Переполнение при вычислении по формуле Кардано.");
            }

            double shift = A / 3;
            Solution result;

            if (D >= 0)
            {
                double u;

                if (q >= 0)
                {
                    u = cbrt(-q / 2 - sqrt(D));
                }
                else
                {
                    u = cbrt(-q / 2 + sqrt(D));
                }

                double v = 0;

                if (u != 0)
                {
                    v = -p / (3 * u);
                }

                double x1 = u + v - shift;
                double realPart = -(u + v) / 2 - shift;
                double imaginaryPart = sqrt(3.0) * (u - v) / 2;

                Complex x2(realPart, imaginaryPart);
                Complex x3(realPart, -imaginaryPart);

                result.roots.push_back(x1);
                result.roots.push_back(x2);
                result.roots.push_back(x3);
            }
            else
            {
                double radius = 2 * sqrt(-p / 3);
                double cosine = -q / (2 * sqrt(-p * p * p / 27));

                if (cosine < -1)
                {
                    cosine = -1;
                }
                else if (cosine > 1)
                {
                    cosine = 1;
                }

                double angle = acos(cosine);
                double pi = acos(-1.0);

                double x1 = radius * cos(angle / 3) - shift;
                double x2 = radius * cos((angle + 2 * pi) / 3) - shift;
                double x3 = radius * cos((angle + 4 * pi) / 3) - shift;

                result.roots.push_back(x1);
                result.roots.push_back(x2);
                result.roots.push_back(x3);
            }

            return result;
        }
    };
}

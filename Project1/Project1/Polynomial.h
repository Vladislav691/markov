#pragma once

#include <cmath>
#include <complex>
#include <limits>
#include <vector>

namespace PolynomialSolver
{
    using namespace std;

    using Complex = complex<double>;

    class Polynomial
    {
    public:
        explicit Polynomial(vector<double> coefficients)
            : coefficients_(coefficients)
        {
            if (coefficients_.size() < 2 || coefficients_.size() > 6)
            {
                throw gcnew System::ArgumentException(L"Поддерживаются степени от 1 до 5.");
            }
            for (double value : coefficients_)
            {
                if (!isfinite(value))
                {
                    throw gcnew System::ArgumentException(L"Коэффициенты должны быть конечными числами.");
                }
            }
            if (Degree() > 1 && coefficients_[0] == 0)
            {
                throw gcnew System::ArgumentException(L"Старший коэффициент не должен быть равен нулю.");
            }
        }

        int Degree() const
        {
            return static_cast<int>(coefficients_.size()) - 1;
        }

        const vector<double>& Coefficients() const
        {
            return coefficients_;
        }

        static double Evaluate(const double* coefficients, int count, double x)
        {
            double value = coefficients[0];
            for (int i = 1; i < count; ++i)
            {
                value = value * x + coefficients[i];
            }
            return value;
        }

        double Evaluate(double x) const
        {
            return Evaluate(coefficients_.data(), static_cast<int>(coefficients_.size()), x);
        }

        Complex Evaluate(Complex x) const
        {
            Complex value = coefficients_[0];
            for (size_t i = 1; i < coefficients_.size(); ++i)
            {
                value = value * x + coefficients_[i];
            }
            return value;
        }

        double RelativeResidual(Complex x) const
        {
            if (!isfinite(x.real()) || !isfinite(x.imag()))
            {
                return numeric_limits<double>::infinity();
            }
            double maximum = 0;
            for (double coefficient : coefficients_)
            {
                double magnitude = abs(coefficient);
                if (magnitude > maximum)
                {
                    maximum = magnitude;
                }
            }
            if (maximum == 0)
            {
                return 0;
            }
            const bool reciprocal = abs(x) > 1;
            Complex argument = x;
            if (reciprocal)
            {
                argument = 1.0 / x;
            }
            Complex value = 0;
            double scale = 0;
            for (size_t i = 0; i < coefficients_.size(); ++i)
            {
                size_t index = i;
                if (reciprocal)
                {
                    index = coefficients_.size() - 1 - i;
                }
                double coefficient = coefficients_[index] / maximum;
                value = value * argument + coefficient;
                scale = scale * abs(argument) + abs(coefficient);
            }
            if (scale < 1.0)
            {
                scale = 1.0;
            }
            const double residual = abs(value) / scale;
            if (!isfinite(residual))
            {
                return numeric_limits<double>::infinity();
            }
            return residual;
        }

    private:
        vector<double> coefficients_;
    };
}

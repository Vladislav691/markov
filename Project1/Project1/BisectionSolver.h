#pragma once

#include <cmath>

#include "EquationSolver.h"

namespace PolynomialSolver
{
    using namespace std;

    struct SearchSettings
    {
        double left = -10;
        double right = 10;
        double step = 0.1;
        double accuracy = 1e-6;

        void Validate() const
        {
            if (!isfinite(left) || !isfinite(right) || !isfinite(step) || !isfinite(accuracy))
            {
                throw gcnew System::ArgumentException(L"Настройки поиска должны быть конечными числами.");
            }
            if (left >= right)
            {
                throw gcnew System::ArgumentException(L"Левая граница должна быть меньше правой.");
            }
            if (step <= 0)
            {
                throw gcnew System::ArgumentException(L"Шаг должен быть больше нуля.");
            }
            if (accuracy <= 0)
            {
                throw gcnew System::ArgumentException(L"Точность должна быть больше нуля.");
            }
            const double count = (right - left) / step;
            if (!isfinite(count) || count > 1000000)
            {
                throw gcnew System::ArgumentException(
                    L"Слишком много участков поиска (максимум 1 000 000). Увеличьте шаг.");
            }
            if (left + step == left && step < right - left)
            {
                throw gcnew System::ArgumentException(
                    L"Шаг слишком мал для выбранных границ и точности double.");
            }
        }
    };

    class BisectionSolver final : public EquationSolver
    {
    public:
        explicit BisectionSolver(SearchSettings settings)
            : settings_(settings)
        {
            settings_.Validate();
        }

        Solution Solve(const Polynomial& polynomial) const override
        {
            if (polynomial.Coefficients()[0] == 0)
            {
                throw gcnew System::ArgumentException(
                    L"Численный поиск требует ненулевой старший коэффициент.");
            }
            Solution result;
            double left = settings_.left;
            double leftValue = CheckedValue(polynomial, left);
            if (leftValue == 0)
            {
                AddRoot(result, left);
            }
            int count = static_cast<int>(ceil((settings_.right - settings_.left) / settings_.step));
            if (count < 1)
            {
                count = 1;
            }
            for (int i = 1; i <= count; ++i)
            {
                double right = settings_.right;
                if (i != count)
                {
                    right = settings_.left + i * settings_.step;
                    if (right > settings_.right)
                    {
                        right = settings_.right;
                    }
                }
                if (right <= left)
                {
                    throw gcnew System::InvalidOperationException(
                        L"Шаг поиска меньше разрешения double в этом диапазоне.");
                }
                const double rightValue = CheckedValue(polynomial, right);
                if (OppositeSigns(leftValue, rightValue))
                {
                    AddRoot(result, Refine(polynomial, left, right));
                }
                if (rightValue == 0)
                {
                    AddRoot(result, right);
                }
                left = right;
                leftValue = rightValue;
            }
            if (result.roots.empty())
            {
                result.kind = SolutionKind::None;
            }
            return result;
        }

    private:
        SearchSettings settings_;

        double Refine(const Polynomial& polynomial, double left, double right) const
        {
            double leftValue = CheckedValue(polynomial, left);
            while (true)
            {
                const double middle = left / 2 + right / 2;
                const double value = CheckedValue(polynomial, middle);
                if (value == 0)
                {
                    return middle;
                }
                if (right / 2 - left / 2 <= settings_.accuracy)
                {
                    return middle;
                }
                if (middle == left || middle == right)
                {
                    throw gcnew System::InvalidOperationException(
                        L"Заданная точность недостижима в double. Увеличьте допустимую погрешность.");
                }
                if (OppositeSigns(leftValue, value))
                {
                    right = middle;
                }
                else
                {
                    left = middle;
                    leftValue = value;
                }
            }
        }

        static void AddRoot(Solution& result, double root)
        {
            if (result.roots.empty() || result.roots.back().real() != root)
            {
                result.roots.push_back(Complex(root, 0));
            }
        }

        static bool OppositeSigns(double left, double right)
        {
            return (left < 0 && right > 0) || (left > 0 && right < 0);
        }

        static double CheckedValue(const Polynomial& polynomial, double x)
        {
            const double value = polynomial.Evaluate(x);
            if (!isfinite(value))
            {
                throw gcnew System::OverflowException(
                    L"Переполнение при вычислении полинома. Уменьшите диапазон или масштаб коэффициентов.");
            }
            return value;
        }
    };
}

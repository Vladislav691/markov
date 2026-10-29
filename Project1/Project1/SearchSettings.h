#pragma once

#include <cmath>
#include <limits>

namespace PolynomialSolver
{
    using namespace std;

    struct SearchSettings
    {
        static constexpr double SearchStep = 0.1;
        static constexpr int MaximumIntervals = 1000000;

        double left = numeric_limits<double>::quiet_NaN();
        double right = numeric_limits<double>::quiet_NaN();
        double step = SearchStep;
        double accuracy = 0.000001;
        bool findAll = false;

        void Validate() const
        {
            if (!isfinite(left) || !isfinite(right) || !isfinite(accuracy))
            {
                throw gcnew System::ArgumentException(L"Настройки поиска должны быть конечными числами.");
            }
            if (left >= right)
            {
                throw gcnew System::ArgumentException(L"Левая граница должна быть меньше правой.");
            }
            if (accuracy <= 0)
            {
                throw gcnew System::ArgumentException(L"Точность должна быть больше нуля.");
            }
            if (findAll)
            {
                if (!isfinite(step) || step <= 0)
                {
                    throw gcnew System::ArgumentException(L"Шаг должен быть больше нуля.");
                }
                const double count = (right - left) / step;
                if (!isfinite(count) || count > MaximumIntervals)
                {
                    throw gcnew System::ArgumentException(
                        L"Слишком много участков поиска (максимум 1 000 000). Уменьшите диапазон поиска.");
                }
                if (left + step == left && step < right - left)
                {
                    throw gcnew System::ArgumentException(
                        L"Шаг слишком мал для выбранных границ и точности double.");
                }
            }
        }
    };

}

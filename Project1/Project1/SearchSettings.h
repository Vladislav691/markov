#pragma once

#include <cmath>

namespace PolynomialSolver
{
    using namespace std;

    struct SearchSettings
    {
        static constexpr double SearchStep = 0.1;
        static constexpr int MaximumIntervals = 1000000;

        double left = -10;
        double right = 10;
        double step = SearchStep;
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
    };

}

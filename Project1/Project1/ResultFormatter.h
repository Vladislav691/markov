#pragma once

#include <cmath>

#include "EquationSolver.h"

namespace PolynomialSolver
{
    namespace UI
    {
        using namespace std;
        using namespace System;
        using namespace System::Text;

        public ref class ResultFormatter abstract sealed
        {
        public:
            static String^ Format(const Solution& solution, bool numerical)
            {
                if (solution.kind == SolutionKind::Infinite)
                {
                    return L"Бесконечно много решений.";
                }

                if (solution.kind == SolutionKind::None)
                {
                    if (numerical)
                    {
                        return L"Корни не обнаружены с заданным шагом. Это не доказывает их отсутствие.";
                    }
                    else
                    {
                        return L"Решений нет.";
                    }
                }

                StringBuilder^ text = gcnew StringBuilder();

                if (solution.roots.size() == 1)
                {
                    text->AppendLine(L"Корень:");
                }
                else if (numerical)
                {
                    text->AppendLine(L"Найденные действительные корни:");
                }
                else
                {
                    text->AppendLine(L"Корни:");
                }

                for (size_t i = 0; i < solution.roots.size(); ++i)
                {
                    Complex root = solution.roots[i];
                    double real = root.real();
                    double imaginary = root.imag();
                    int number = static_cast<int>(i + 1);

                    if (imaginary == 0)
                    {
                        text->AppendFormat(L"x{0} = {1:G12}", number, real);
                    }
                    else
                    {
                        String^ sign = L"+";

                        if (imaginary < 0)
                        {
                            sign = L"−";
                        }

                        text->AppendFormat(
                            L"x{0} = {1:G12} {2} {3:G12}i",
                            number,
                            real,
                            sign,
                            abs(imaginary)
                        );
                    }

                    text->AppendLine();
                }

                if (!solution.verified)
                {
                    text->AppendLine(L"Для уточнения корней уменьшите допустимую погрешность.");
                }

                return text->ToString();
            }
        };
    }
}
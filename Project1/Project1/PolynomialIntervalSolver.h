#pragma once
#include <cmath>
using namespace System;
public ref class PolynomialIntervalSolver
{
private:
	cli::array<double>^ coefficients;
	double Calculate(double x)
	{
		double value = 0;
		for each (double coefficient in coefficients)
			value = value * x + coefficient;
		return value;
	}
public:
	PolynomialIntervalSolver(cli::array<double>^ values)
	{
		if (values == nullptr || values->Length < 3 || values->Length > 6)
			throw gcnew ArgumentException(L"Поддерживаются степени от 2 до 5");
		coefficients = safe_cast<cli::array<double>^>(values->Clone());
	}
	double Solve(double left, double right)
	{
		if (coefficients[0] == 0)
			throw gcnew ArgumentException(L"Коэффициент a не должен быть равен нулю");
		for each (double coefficient in coefficients)
		{
			if (Double::IsNaN(coefficient) || Double::IsInfinity(coefficient))
				throw gcnew ArgumentException(L"Введите конечные числовые коэффициенты");
		}
		if (Double::IsNaN(left) || Double::IsInfinity(left) ||
			Double::IsNaN(right) || Double::IsInfinity(right))
		{
			throw gcnew ArgumentException(L"Введите конечные числовые границы отрезка");
		}
		if (left >= right)
		{
			throw gcnew ArgumentException(L"Левая граница должна быть меньше правой");
		}
		double leftValue = Calculate(left);
		double rightValue = Calculate(right);

		if (Double::IsNaN(leftValue) || Double::IsInfinity(leftValue) ||
			Double::IsNaN(rightValue) || Double::IsInfinity(rightValue))
		{
			throw gcnew ArgumentException(L"Слишком большие значения для вычисления");
		}

		if (leftValue == 0)
		{
			return left;
		}
		if (rightValue == 0)
		{
			return right;
		}
		if ((leftValue > 0 && rightValue > 0) ||
			(leftValue < 0 && rightValue < 0))
		{
			throw gcnew ArgumentException(L"На концах отрезка функция имеет одинаковый знак. Выберите другой отрезок.");
		}

		const double accuracy = 0.000001;
		// Постепенно сужаем отрезок, содержащий корень.
		while (true)
		{
			double middle = left / 2.0 + right / 2.0;
			double middleValue = Calculate(middle);

			if (Double::IsNaN(middleValue) ||
				Double::IsInfinity(middleValue))
			{
				throw gcnew ArgumentException(L"Слишком большие значения для вычисления");
			}

			if (middleValue == 0 ||
				Math::Abs(right / 2.0 - left / 2.0) <= accuracy)
			{
				return middle;
			}

			// Дальнейшее деление невозможно из-за точности double.
			if (middle == left || middle == right)
				throw gcnew ArgumentException(L"Не удалось достичь заданной точности. Выберите более узкий отрезок.");

			if ((leftValue < 0 && middleValue > 0) ||
				(leftValue > 0 && middleValue < 0))
			{
				right = middle;
			}
			else
			{
				left = middle;
				leftValue = middleValue;
			}
		}
	}
};
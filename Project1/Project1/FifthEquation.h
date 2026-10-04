#pragma once
#include <cmath>
using namespace System;
public ref class FifthEquation
{
private:
	double a, b, c, d, e, f;
	double Calculate(double x)
	{
		return (((((a * x + b) * x + c) * x + d) * x + e) * x + f);
	}
public:
	FifthEquation(
		double a, double b, double c,
		double d, double e, double f)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->e = e;
		this->f = f;
	}
	double Solve(double left, double right)
	{
		if (a == 0)
		{
			throw gcnew ArgumentException(L"Коэффициент a не должен быть равен нулю");
		}
		if (Double::IsNaN(a) || Double::IsInfinity(a) ||
			Double::IsNaN(b) || Double::IsInfinity(b) ||
			Double::IsNaN(c) || Double::IsInfinity(c) ||
			Double::IsNaN(d) || Double::IsInfinity(d) ||
			Double::IsNaN(e) || Double::IsInfinity(e) ||
			Double::IsNaN(f) || Double::IsInfinity(f))
		{
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
#pragma once
#include "QuarticEquation.h"
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
	String^ Solve()
	{
		if (a == 0)
		{
			return L"Коэффициент a не должен быть равен нулю";
		}
		if (Double::IsNaN(a) || Double::IsInfinity(a) ||
			Double::IsNaN(b) || Double::IsInfinity(b) ||
			Double::IsNaN(c) || Double::IsInfinity(c) ||
			Double::IsNaN(d) || Double::IsInfinity(d) ||
			Double::IsNaN(e) || Double::IsInfinity(e) ||
			Double::IsNaN(f) || Double::IsInfinity(f))
		{
			return L"Введите конечные числовые коэффициенты";
		}

		if (f == 0)
		{
			QuarticEquation^ equation = gcnew QuarticEquation();

			String^ otherRoots = equation->solveQuarticFerrari(a, b, c, d, e);

			return L"Один корень: x = 0\n"
				L"Остальные четыре корня:\n" + otherRoots;
		}
		double R = Math::Abs(b / a);
		R = Math::Max(R, Math::Abs(c / a));
		R = Math::Max(R, Math::Abs(d / a));
		R = Math::Max(R, Math::Abs(e / a));
		R = Math::Max(R, Math::Abs(f / a));
		R += 1;
		if (Double::IsInfinity(R))
		{
			return L"Слишком большая разница между коэффициентами";
		}
		double left = -R;
		double right = R;
		double leftValue = Calculate(left);
		double rightValue = Calculate(right);

		if (Double::IsNaN(leftValue) || Double::IsInfinity(leftValue) ||
			Double::IsNaN(rightValue) || Double::IsInfinity(rightValue))
		{
			return L"Слишком большие значения для вычисления";
		}

		if (leftValue == 0)
		{
			return String::Format(L"x = {0:G10}", left);
		}
		if (rightValue == 0)
		{
			return String::Format(L"x = {0:G10}", right);
		}
		if ((leftValue > 0 && rightValue > 0) ||
			(leftValue < 0 && rightValue < 0))
		{
			return L"Не удалось подобрать отрезок из-за погрешности вычислений";
		}

		const double accuracy = 0.000001;
		// Постепенно сужаем отрезок, содержащий корень.
		for (int i = 0; i < 200; i++)
		{
			double middle = left / 2.0 + right / 2.0;
			double middleValue = Calculate(middle);

			if (Double::IsNaN(middleValue) ||
				Double::IsInfinity(middleValue))
			{
				return L"Слишком большие значения для вычисления";
			}

			if (middleValue == 0 ||
				Math::Abs(right / 2.0 - left / 2.0) <= accuracy)
			{
				return String::Format(L"x ≈ {0:G10}", middle);
			}

			// Дальнейшее деление невозможно из-за точности double.
			if (middle == left || middle == right)
				return L"Не удалось достичь заданной точности";

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
		return L"Не удалось достичь заданной точности";
	}
};
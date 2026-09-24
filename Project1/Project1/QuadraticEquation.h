#pragma once

using namespace System;
public ref class QuadraticEquation
{
private:
	double a, b, c;
public:
	QuadraticEquation(double a, double b, double c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	String^ Solve()
	{
		if (a == 0)
		{
			return "Это не квадратное уравнение, a = 0";
		}
		double D = b * b - 4 * a * c;
		if (D < 0)
		{
			double realPart = -b / (2 * a);
			double imagPart = Math::Sqrt(-D) / (2 * Math::Abs(a));
			return String::Format("x1 = {0} + {1}i; x2 = {0} - {1}i", realPart, imagPart);
		}
		if (D == 0)
		{
			double x = -b / (2 * a);
			return String::Format("Один корень: x = {0}", x);
		}
		if (D > 0)
		{
			double x1 = (-b + Math::Sqrt(D)) / (2 * a);
			double x2 = (-b - Math::Sqrt(D)) / (2 * a);
			return String::Format("x1 = {0}; x2 = {1}", x1, x2);
		}

		return "Не удалось вычислить корни: проверьте коэффициенты";
	}
	
};

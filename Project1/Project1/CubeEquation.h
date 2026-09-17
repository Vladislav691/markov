#pragma once
#include <cmath>
using namespace System;
public ref class CubeEquation
{
private:
	double a, b, c, d;
	double cbrt_real(double x)
	{
		return (x < 0) ? -pow(-x, 1.0 / 3.0) : pow(x, 1.0 / 3.0);
	}
public:
	CubeEquation(double a, double b, double c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
	array<String^>^ Solve(bool showComplex)
	{
		//проверка на корректность
		if (abs(a) < 1e-9)
		{
			array<String^>^ err = gcnew array<String^>(1);
			err[0] = "Ошибка: 'a' не должно быть равно 0(уравнение не кубическое)";
			return err;
		}
		double A = b / a;
		double B = c / a;
		double C = d / a;

		double p = B - (A * A) / 3.0;
		double q = C - (A * B) / 3.0 + (2.0 * A * A * A) / 27.0;
		double D = (q * q) / 4.0 + (p * p * p) / 27.0;

		double shift = A / 3.0;
		const double EPS = 1e-9;
		
		if (D > EPS)
		{
			//Случай 1: действительный корень и 2 комплексных
			double u = cbrt_real(-q / 2.0 + sqrt(D));
			double v = cbrt_real(-q / 2.0 - sqrt(D));

			double realPart1 = (u + v) - shift;
			double realPart23 = -0.5 * (u + v) - shift;
			double imagPart = (u - v) * sqrt(3.0) / 2.0;
			if (showComplex)
			{
				array<String^>^ result = gcnew array<String^>(3);
				result[0] = "x1 = " + realPart1.ToString("F6");
				result[1] = "x2 = " + realPart23.ToString("F6") + " + " + abs(imagPart).ToString("F6") + "i";
				result[2] = "x3 = " + realPart23.ToString("F6") + " - " + abs(imagPart).ToString("F6") + "i";
				return result;
			}
			else
			{
				array<String^>^ result = gcnew array<String^>(2);
				result[0] = "x1 = " + realPart1.ToString("F6");
				result[1] = "Комплексные числа скрыты";
				return result;
			}
		}
		
	}
};
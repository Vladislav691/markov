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
	CubeEquation(double a, double b, double c, double d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
	String^ Solve()
	{
		//проверка на корректность
		if (abs(a) < 1e-9)
		{
			return "Ошибка: 'a'не должно быть равно 0";
		}
		double A = b / a;
		double B = c / a;
		double C = d / a;

		double p = B - (A * A) / 3.0;
		double q = C - (A * B) / 3.0 + (2.0 * A * A * A) / 27.0;
		double D = (q * q) / 4.0 + (p * p * p) / 27.0;

		double shift = A / 3.0;
		const double EPS = 1e-9;
		
		String^ result = "";
		if (D > EPS)
		{
			double u = cbrt_real(-q / 2.0 + sqrt(D));
			double v = cbrt_real(-q / 2.0 - sqrt(D));

			double realPart1 = (u + v) - shift;
			double realPart23 = -0.5 * (u + v) - shift;
			double imagPart = (u - v) * sqrt(3.0) / 2.0;
			result += "x1 = " + realPart1.ToString("F6") + "\n";
			result += "x2 = " + realPart23.ToString("F6") + " + " + abs(imagPart).ToString("F6") + "i\n";
			result += "x3 = " + realPart23.ToString("F6") + " - " + abs(imagPart).ToString("F6") + "i\n";
		}
		else
		{
			double r = sqrt(-(p * p * p) / 27.0);
			double phi = (abs(r) < EPS) ? 0 : acos(-q / (2.0 * r));
			double factor = 2.0 * cbrt_real(r);

			double x1 = factor * cos(phi / 3.0) - shift;
			double x2 = factor * cos((phi + 2.0 * Math::PI) / 3.0) - shift;
			double x3 = factor * cos((phi + 4.0 * Math::PI) / 3.0) - shift;

			result += "x1 = " + x1.ToString("F6") + "\n";
			result += "x2 = " + x2.ToString("F6") + "\n";
			result += "x3 = " + x3.ToString("F6") + "\n";
		}
		return result;
		
	}
};
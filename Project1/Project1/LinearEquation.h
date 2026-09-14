#pragma once

using namespace System;
public ref class LinearEquation
{
private:
	double a;
	double b;
public:
	LinearEquation(double a, double b)
	{
		this->a = a;
		this->b = b;
	}
	String^ Solve()
	{
		if (a == 0 && b == 0)
		{
			return "Бесконечно много решений";
		}
		if (a == 0)
		{
			return "решений нет";
		}
		double x = -b / a;
		return String::Format("x = {0}", x);
	}
};
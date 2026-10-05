#pragma once
#include "PolynomialIntervalSolver.h"
using namespace System;
public ref class FifthEquation
{
private:
	PolynomialIntervalSolver^ solver;
public:
	FifthEquation(double a, double b, double c, double d, double e, double f)
	{
		solver = gcnew PolynomialIntervalSolver(gcnew cli::array<double> { a, b, c, d, e, f });
	}
	double Solve(double left, double right)
	{
		return solver->Solve(left, right);
	}
};

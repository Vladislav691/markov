#include "MyForm.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace
{
	double EvaluatePolynomial(const std::vector<double>& coefficients, double x)
	{
		double value = 0.0;
		for (double coefficient : coefficients)
		{
			value = value * x + coefficient;
		}
		return value;
	}

	double EvaluationScale(const std::vector<double>& coefficients, double x)
	{
		double scale = 0.0;
		for (double coefficient : coefficients)
		{
			scale = scale * std::max(1.0, std::abs(x)) + std::abs(coefficient);
		}
		return std::max(1.0, scale);
	}

	void AddUniqueRoot(std::vector<double>& roots, double root)
	{
		for (double existing : roots)
		{
			if (std::abs(existing - root) <= 1e-6 * std::max(1.0, std::abs(root)))
			{
				return;
			}
		}
		roots.push_back(root);
	}

	std::vector<double> FindRealRoots(std::vector<double> coefficients)
	{
		while (coefficients.size() > 1 && std::abs(coefficients.front()) < 1e-12)
		{
			coefficients.erase(coefficients.begin());
		}

		const int degree = static_cast<int>(coefficients.size()) - 1;
		if (degree < 1)
		{
			return {};
		}
		if (degree == 1)
		{
			return { -coefficients[1] / coefficients[0] };
		}

		std::vector<double> derivative;
		derivative.reserve(degree);
		for (int i = 0; i < degree; ++i)
		{
			derivative.push_back(coefficients[i] * (degree - i));
		}

		std::vector<double> criticalPoints = FindRealRoots(derivative);
		std::sort(criticalPoints.begin(), criticalPoints.end());

		double bound = 1.0;
		for (std::size_t i = 1; i < coefficients.size(); ++i)
		{
			bound = std::max(bound, 1.0 + std::abs(coefficients[i] / coefficients[0]));
		}

		std::vector<double> points;
		points.push_back(-bound);
		for (double point : criticalPoints)
		{
			if (point > -bound && point < bound)
			{
				points.push_back(point);
			}
		}
		points.push_back(bound);

		std::vector<double> roots;
		for (double point : points)
		{
			const double value = EvaluatePolynomial(coefficients, point);
			if (std::abs(value) <= 1e-9 * EvaluationScale(coefficients, point))
			{
				AddUniqueRoot(roots, point);
			}
		}

		for (std::size_t i = 0; i + 1 < points.size(); ++i)
		{
			double left = points[i];
			double right = points[i + 1];
			double leftValue = EvaluatePolynomial(coefficients, left);
			double rightValue = EvaluatePolynomial(coefficients, right);

			if (!((leftValue < 0.0 && rightValue > 0.0) ||
				(leftValue > 0.0 && rightValue < 0.0)))
			{
				continue;
			}

			for (int iteration = 0; iteration < 100; ++iteration)
			{
				const double middle = (left + right) / 2.0;
				const double middleValue = EvaluatePolynomial(coefficients, middle);

				if ((leftValue < 0.0 && middleValue > 0.0) ||
					(leftValue > 0.0 && middleValue < 0.0))
				{
					right = middle;
					rightValue = middleValue;
				}
				else
				{
					left = middle;
					leftValue = middleValue;
				}
			}

			AddUniqueRoot(roots, (left + right) / 2.0);
		}

		std::sort(roots.begin(), roots.end());
		return roots;
	}
}

namespace Project1
{
	void MyForm::InitializeGraphPanel()
	{
		graphPanel = gcnew PolynomialSolver::UI::GraphPanel();
		graphPanel->Location = System::Drawing::Point(430, 225);
		graphPanel->Size = System::Drawing::Size(
			ClientSize.Width - 455,
			ClientSize.Height - 250);
		graphPanel->Anchor = AnchorStyles::Top | AnchorStyles::Bottom |
			AnchorStyles::Left | AnchorStyles::Right;
		graphPanel->BorderStyle = BorderStyle::FixedSingle;
		Controls->Add(graphPanel);
		graphPanel->BringToFront();
	}

	void MyForm::ShowPolynomial(cli::array<double>^ coefficients)
	{
		std::vector<double> nativeCoefficients;
		for each (double coefficient in coefficients)
		{
			nativeCoefficients.push_back(coefficient);
		}

		const std::vector<double> roots = FindRealRoots(nativeCoefficients);
		cli::array<double>^ managedRoots = gcnew cli::array<double>(static_cast<int>(roots.size()));
		for (int i = 0; i < managedRoots->Length; ++i)
		{
			managedRoots[i] = roots[i];
		}

		graphPanel->SetPolynomial(coefficients, managedRoots);
	}

	System::Void MyForm::comboBoxDegree_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		panelLinear->Visible = false;
		panelQuadratic->Visible = false;
		panelCube->Visible = false;
		panelQuartic->Visible = false;
		graphPanel->ClearGraph();

		if (comboBoxDegree->Text == "1")
		{
			panelLinear->Visible = true;
		}
		else if (comboBoxDegree->Text == "2")
		{
			panelQuadratic->Visible = true;
		}
		else if (comboBoxDegree->Text == "3")
		{
			panelCube->Visible = true;
		}
		else if (comboBoxDegree->Text == "4")
		{
			panelQuartic->Visible = true;
		}
	}

	System::Void MyForm::buttonSolve_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			if (comboBoxDegree->Text == "1")
			{
				double a = Double::Parse(textBoxLinearA->Text);
				double b = Double::Parse(textBoxLinearB->Text);
				LinearEquation^ equation = gcnew LinearEquation(a, b);
				labelResult->Text = equation->Solve();
				ShowPolynomial(gcnew cli::array<double> { a, b });
			}
			else if (comboBoxDegree->Text == "2")
			{
				double a = Double::Parse(textBoxQuadraticA->Text);
				double b = Double::Parse(textBoxQuadraticB->Text);
				double c = Double::Parse(textBoxQuadraticC->Text);

				QuadraticEquation^ equation = gcnew QuadraticEquation(a, b, c);
				labelResult->Text = equation->Solve();
				ShowPolynomial(gcnew cli::array<double> { a, b, c });
			}
			else if (comboBoxDegree->Text == "3")
			{
				double a = Double::Parse(textBoxCubeA->Text);
				double b = Double::Parse(textBoxCubeB->Text);
				double c = Double::Parse(textBoxCubeC->Text);
				double d = Double::Parse(textBoxCubeD->Text);

				CubeEquation^ equation = gcnew CubeEquation(a, b, c, d);
				labelResult->Text = equation->Solve();
				ShowPolynomial(gcnew cli::array<double> { a, b, c, d });
			}
			else if (comboBoxDegree->Text == "4")
			{
				double a = Double::Parse(textBoxQuarticA->Text);
				double b = Double::Parse(textBoxQuarticB->Text);
				double c = Double::Parse(textBoxQuarticC->Text);
				double d = Double::Parse(textBoxQuarticD->Text);
				double e = Double::Parse(textBoxQuarticE->Text);

				QuarticEquation^ equation = gcnew QuarticEquation();
				labelResult->Text = equation->solveQuarticFerrari(a, b, c, d, e);
				ShowPolynomial(gcnew cli::array<double> { a, b, c, d, e });
			}
		}
		catch (FormatException^)
		{
			labelResult->Text = "Введите только числа!";
			graphPanel->ClearGraph();
		}
	}
}

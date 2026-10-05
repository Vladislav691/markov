#include "MyForm.h"
#include "FifthEquation.h"
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
			scale = scale * std::abs(x) + std::abs(coefficient);
		}
		return scale;
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
		while (coefficients.size() > 1 && coefficients.front() == 0.0)
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
				if (middleValue == 0.0)
				{
					left = middle;
					right = middle;
					break;
				}

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
		graphPanel->Dock = DockStyle::Fill;
		graphPanel->BorderStyle = BorderStyle::FixedSingle;
		panelGraph->Controls->Add(graphPanel);
		graphPanel->BringToFront();
		comboBoxDegree->SelectedIndex = 0;
	}

	void MyForm::InitializeSolutionControls()
	{
		Panel^ buttonHost = gcnew Panel();
		buttonHost->Size = buttonSolve->Size;
		buttonHost->Margin = buttonSolve->Margin;
		buttonHost->Anchor = buttonSolve->Anchor;
		layoutResult->Controls->Remove(buttonSolve);
		layoutResult->Controls->Add(buttonHost, 0, 0);
		buttonSolve->Dock = DockStyle::Fill;
		buttonHost->Controls->Add(buttonSolve);

		buttonReset = gcnew Button();
		buttonReset->Name = L"buttonReset";
		buttonReset->Text = L"Сбросить";
		buttonReset->Font = buttonSolve->Font;
		buttonReset->Dock = DockStyle::Fill;
		buttonReset->UseVisualStyleBackColor = true;
		buttonReset->Click += gcnew EventHandler(this, &MyForm::buttonReset_Click);
		buttonHost->Controls->Add(buttonReset);
		panelInterval = gcnew Panel();
		panelInterval->Name = L"panelInterval";
		panelInterval->Dock = DockStyle::Bottom;
		panelInterval->Height = 36;
		panelInterval->Visible = false;
		panelEquation->Controls->Add(panelInterval);
		panelInterval->SendToBack();
		Label^ labelLeft = gcnew Label();
		labelLeft->Text = L"Левая граница:";
		labelLeft->AutoSize = true;
		labelLeft->Location = Point(11, 8);
		panelInterval->Controls->Add(labelLeft);
		textBoxIntervalLeft = gcnew TextBox();
		textBoxIntervalLeft->Name = L"textBoxIntervalLeft";
		textBoxIntervalLeft->Location = Point(115, 5);
		textBoxIntervalLeft->Width = 90;
		textBoxIntervalLeft->TabIndex = 15;
		panelInterval->Controls->Add(textBoxIntervalLeft);

		Label^ labelRight = gcnew Label();
		labelRight->Text = L"Правая граница:";
		labelRight->AutoSize = true;
		labelRight->Location = Point(225, 8);
		panelInterval->Controls->Add(labelRight);
		textBoxIntervalRight = gcnew TextBox();
		textBoxIntervalRight->Name = L"textBoxIntervalRight";
		textBoxIntervalRight->Location = Point(335, 5);
		textBoxIntervalRight->Width = 90;
		textBoxIntervalRight->TabIndex = 16;
		panelInterval->Controls->Add(textBoxIntervalRight);
		SetSolutionLocked(false);
	}

	void MyForm::SetSolutionLocked(bool locked)
	{
		for each (Control^ panel in panelEquationHost->Controls)
		{
			for each (Control^ control in panel->Controls)
			{
				TextBox^ coefficient = dynamic_cast<TextBox^>(control);
				if (coefficient != nullptr)
				{
					coefficient->ReadOnly = locked;
				}
			}
		}
		textBoxIntervalLeft->ReadOnly = locked;
		textBoxIntervalRight->ReadOnly = locked;
		comboBoxDegree->Enabled = !locked;
		buttonSolve->Visible = !locked;
		buttonReset->Visible = locked;
		// Enter solves during editing, but must not accidentally reset a result.
		AcceptButton = locked ? nullptr : buttonSolve;
		if (locked)
		{
			buttonReset->BringToFront();
			buttonReset->Focus();
		}
		else
		{
			buttonSolve->BringToFront();
		}
	}

	System::Void MyForm::buttonReset_Click(System::Object^ sender, System::EventArgs^ e)
	{
		labelResult->Text = L"Результат:";
		graphPanel->ClearGraph();
		SetSolutionLocked(false);
		for each (Control^ panel in panelEquationHost->Controls)
		{
			if (panel->Visible)
			{
				panel->SelectNextControl(nullptr, true, true, false, false);
				break;
			}
		}
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
		panelLinear->Visible = comboBoxDegree->Text == "1";
		panelQuadratic->Visible = comboBoxDegree->Text == "2";
		panelCube->Visible = comboBoxDegree->Text == "3";
		panelQuartic->Visible = comboBoxDegree->Text == "4";
		panelFifth->Visible = comboBoxDegree->Text == "5";
		bool needsInterval = comboBoxDegree->SelectedIndex >= 1;
		if (panelInterval != nullptr)
			panelInterval->Visible = needsInterval;
		tableLayoutPanel1->RowStyles[1]->Height = needsInterval ? 112.0F : 76.0F;

		labelResult->Text = L"Результат:";
		graphPanel->ClearGraph();
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
			else
			{
				cli::array<TextBox^>^ fields;
				switch (comboBoxDegree->SelectedIndex)
				{
				case 1:
				{
					fields = gcnew cli::array<TextBox^> { textBoxQuadraticA, textBoxQuadraticB, textBoxQuadraticC };
					break;
				}
				case 2:
				{
					fields = gcnew cli::array<TextBox^> { textBoxCubeA, textBoxCubeB, textBoxCubeC, textBoxCubeD };
					break;
				}
				case 3:
				{
					fields = gcnew cli::array<TextBox^> { textBoxQuarticA, textBoxQuarticB, textBoxQuarticC, textBoxQuarticD, textBoxQuarticE };
					break;
				}
				case 4:
				{
					fields = gcnew cli::array<TextBox^> { textBoxFifthA, textBoxFifthB, textBoxFifthC, textBoxFifthD, textBoxFifthE, textBoxFifthF };
					break;
				}
				default:
					throw gcnew ArgumentException(L"Выберите степень уравнения");
				}
				cli::array<double>^ coefficients = gcnew cli::array<double>(fields->Length);
				for (int i = 0; i < fields->Length; ++i)
					coefficients[i] = Double::Parse(fields[i]->Text);
				PolynomialIntervalSolver^ equation = gcnew PolynomialIntervalSolver(coefficients);
				bool leftMissing = String::IsNullOrWhiteSpace(textBoxIntervalLeft->Text);
				bool rightMissing = String::IsNullOrWhiteSpace(textBoxIntervalRight->Text);
				if (leftMissing || rightMissing)
				{
					labelResult->Text = leftMissing && rightMissing
						? L"Введите левую и правую границы отрезка!"
						: (leftMissing ? L"Введите левую границу отрезка!"
							: L"Введите правую границу отрезка!");
					graphPanel->ClearGraph();
					(leftMissing ? textBoxIntervalLeft : textBoxIntervalRight)->Focus();
					return;
				}
				double left;
				double right;
				if (!Double::TryParse(textBoxIntervalLeft->Text, left))
				{
					labelResult->Text = L"Левая граница должна быть числом!";
					graphPanel->ClearGraph();
					textBoxIntervalLeft->Focus();
					return;
				}
				if (!Double::TryParse(textBoxIntervalRight->Text, right))
				{
					labelResult->Text = L"Правая граница должна быть числом!";
					graphPanel->ClearGraph();
					textBoxIntervalRight->Focus();
					return;
				}
				double root = equation->Solve(left, right);
				labelResult->Text = String::Format(L"Корень на [{0}; {1}]: x ≈ {2:G10}", left, right, root);
				graphPanel->SetPolynomial(coefficients,
					gcnew cli::array<double> { root });
			}
			SetSolutionLocked(true);
		}
		catch (FormatException^)
		{
			labelResult->Text = "Введите только числа!";
			graphPanel->ClearGraph();
		}
		catch (OverflowException^)
		{
			labelResult->Text = L"Введённое число слишком велико";
			graphPanel->ClearGraph();
		}
		catch (ArgumentException^ error)
		{
			labelResult->Text = error->Message;
			graphPanel->ClearGraph();
		}
	}
}

#include "MyForm.h"

namespace Project1
{
	System::Void MyForm::comboBoxDegree_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
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
			}
			else if (comboBoxDegree->Text == "2")
			{
				double a = Double::Parse(textBoxQuadraticA->Text);
				double b = Double::Parse(textBoxQuadraticB->Text);
				double c = Double::Parse(textBoxQuadraticC->Text);

				QuadraticEquation^ equation = gcnew QuadraticEquation(a, b, c);
				labelResult->Text = equation->Solve();
			}
			else if (comboBoxDegree->Text == "3")
			{
				double a = Double::Parse(textBoxCubeA->Text);
				double b = Double::Parse(textBoxCubeB->Text);
				double c = Double::Parse(textBoxCubeC->Text);
				double d = Double::Parse(textBoxCubeD->Text);

				CubeEquation^ equation = gcnew CubeEquation(a, b, c, d);
				labelResult->Text = equation->Solve();
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
			}
		}
		catch (FormatException^)
		{
			labelResult->Text = "Введите только числа!";
		}
	}
}

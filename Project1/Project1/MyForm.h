#pragma once
#include "LinearEquation.h"
#include "QuadraticEquation.h"
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ comboBoxDegree;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Panel^ panelLinear;
	private: System::Windows::Forms::Panel^ panelQuadratic;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBoxLinearB;

	private: System::Windows::Forms::TextBox^ textBoxLinearA;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBoxQuadraticA;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBoxQuadraticC;

	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBoxQuadraticB;
	private: System::Windows::Forms::Button^ buttonSolve;
	private: System::Windows::Forms::Label^ labelResult;


	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->comboBoxDegree = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panelLinear = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxLinearB = (gcnew System::Windows::Forms::TextBox());
			this->textBoxLinearA = (gcnew System::Windows::Forms::TextBox());
			this->panelQuadratic = (gcnew System::Windows::Forms::Panel());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuadraticA = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuadraticC = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuadraticB = (gcnew System::Windows::Forms::TextBox());
			this->buttonSolve = (gcnew System::Windows::Forms::Button());
			this->labelResult = (gcnew System::Windows::Forms::Label());
			this->panelLinear->SuspendLayout();
			this->panelQuadratic->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(53, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(193, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"¬ведите степень уравнени€";
			// 
			// comboBoxDegree
			// 
			this->comboBoxDegree->FormattingEnabled = true;
			this->comboBoxDegree->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"1", L"2", L"3", L"4", L"5" });
			this->comboBoxDegree->Location = System::Drawing::Point(264, 27);
			this->comboBoxDegree->Name = L"comboBoxDegree";
			this->comboBoxDegree->Size = System::Drawing::Size(138, 21);
			this->comboBoxDegree->TabIndex = 1;
			this->comboBoxDegree->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBoxDegree_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(53, 87);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(154, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L"–еши уравнение вида:";
			// 
			// panelLinear
			// 
			this->panelLinear->Controls->Add(this->label4);
			this->panelLinear->Controls->Add(this->label3);
			this->panelLinear->Controls->Add(this->textBoxLinearB);
			this->panelLinear->Controls->Add(this->textBoxLinearA);
			this->panelLinear->Location = System::Drawing::Point(54, 117);
			this->panelLinear->Name = L"panelLinear";
			this->panelLinear->Size = System::Drawing::Size(282, 34);
			this->panelLinear->TabIndex = 3;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(118, 10);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 20);
			this->label4->TabIndex = 3;
			this->label4->Text = L"=  0";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(47, 10);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 20);
			this->label3->TabIndex = 2;
			this->label3->Text = L"x +";
			// 
			// textBoxLinearB
			// 
			this->textBoxLinearB->Location = System::Drawing::Point(77, 10);
			this->textBoxLinearB->Name = L"textBoxLinearB";
			this->textBoxLinearB->Size = System::Drawing::Size(33, 20);
			this->textBoxLinearB->TabIndex = 1;
			// 
			// textBoxLinearA
			// 
			this->textBoxLinearA->Location = System::Drawing::Point(11, 10);
			this->textBoxLinearA->Name = L"textBoxLinearA";
			this->textBoxLinearA->Size = System::Drawing::Size(33, 20);
			this->textBoxLinearA->TabIndex = 0;
			// 
			// panelQuadratic
			// 
			this->panelQuadratic->Controls->Add(this->label7);
			this->panelQuadratic->Controls->Add(this->textBoxQuadraticA);
			this->panelQuadratic->Controls->Add(this->label5);
			this->panelQuadratic->Controls->Add(this->textBoxQuadraticC);
			this->panelQuadratic->Controls->Add(this->label6);
			this->panelQuadratic->Controls->Add(this->textBoxQuadraticB);
			this->panelQuadratic->Location = System::Drawing::Point(54, 175);
			this->panelQuadratic->Name = L"panelQuadratic";
			this->panelQuadratic->Size = System::Drawing::Size(282, 37);
			this->panelQuadratic->TabIndex = 4;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(47, 14);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(45, 20);
			this->label7->TabIndex = 9;
			this->label7->Text = L"x^2 +";
			// 
			// textBoxQuadraticA
			// 
			this->textBoxQuadraticA->Location = System::Drawing::Point(11, 14);
			this->textBoxQuadraticA->Name = L"textBoxQuadraticA";
			this->textBoxQuadraticA->Size = System::Drawing::Size(33, 20);
			this->textBoxQuadraticA->TabIndex = 8;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(215, 14);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 20);
			this->label5->TabIndex = 7;
			this->label5->Text = L"=  0";
			// 
			// textBoxQuadraticC
			// 
			this->textBoxQuadraticC->Location = System::Drawing::Point(170, 14);
			this->textBoxQuadraticC->Name = L"textBoxQuadraticC";
			this->textBoxQuadraticC->Size = System::Drawing::Size(39, 20);
			this->textBoxQuadraticC->TabIndex = 5;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(141, 14);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(29, 20);
			this->label6->TabIndex = 6;
			this->label6->Text = L"x +";
			// 
			// textBoxQuadraticB
			// 
			this->textBoxQuadraticB->Location = System::Drawing::Point(93, 14);
			this->textBoxQuadraticB->Name = L"textBoxQuadraticB";
			this->textBoxQuadraticB->Size = System::Drawing::Size(45, 20);
			this->textBoxQuadraticB->TabIndex = 4;
			// 
			// buttonSolve
			// 
			this->buttonSolve->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonSolve->Location = System::Drawing::Point(467, 113);
			this->buttonSolve->Name = L"buttonSolve";
			this->buttonSolve->Size = System::Drawing::Size(94, 44);
			this->buttonSolve->TabIndex = 5;
			this->buttonSolve->Text = L"–ешить";
			this->buttonSolve->UseVisualStyleBackColor = true;
			this->buttonSolve->Click += gcnew System::EventHandler(this, &MyForm::buttonSolve_Click);
			// 
			// labelResult
			// 
			this->labelResult->AutoSize = true;
			this->labelResult->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelResult->Location = System::Drawing::Point(463, 175);
			this->labelResult->Name = L"labelResult";
			this->labelResult->Size = System::Drawing::Size(113, 24);
			this->labelResult->TabIndex = 6;
			this->labelResult->Text = L"–езультат: ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(979, 539);
			this->Controls->Add(this->labelResult);
			this->Controls->Add(this->buttonSolve);
			this->Controls->Add(this->panelQuadratic);
			this->Controls->Add(this->panelLinear);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBoxDegree);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->panelLinear->ResumeLayout(false);
			this->panelLinear->PerformLayout();
			this->panelQuadratic->ResumeLayout(false);
			this->panelQuadratic->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void comboBoxDegree_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (comboBoxDegree->Text == "1")
		{
			panelLinear->Visible = true;
			panelQuadratic->Visible = false;
		}
		else if (comboBoxDegree->Text == "2")
		{
			panelLinear->Visible = false;
			panelQuadratic->Visible = true;
		}
	}
	private: System::Void buttonSolve_Click(System::Object^ sender, System::EventArgs^ e) 
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
		}
		catch (FormatException^)
		{
			labelResult->Text = "¬ведите только числа!";
		}
	}
};
}

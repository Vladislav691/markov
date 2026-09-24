#pragma once
#include "LinearEquation.h"
#include "QuadraticEquation.h"
#include "QuarticEquation.h"
#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include "CubeEquation.h"
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
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
		/// Освободить все используемые ресурсы.
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
	private: System::Windows::Forms::Panel^ panelCube;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::TextBox^ textBoxCubeA;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBoxCubeB;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ textBoxCubeD;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ textBoxCubeC;
	private: System::Windows::Forms::Panel^ panelQuartic;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBoxQuarticA;
	private: System::Windows::Forms::TextBox^ textBoxQuarticB;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::TextBox^ textBoxQuarticC;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ textBoxQuarticE;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ textBoxQuarticD;




	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
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
			this->panelCube = (gcnew System::Windows::Forms::Panel());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBoxCubeA = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBoxCubeB = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBoxCubeD = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBoxCubeC = (gcnew System::Windows::Forms::TextBox());
			this->panelQuartic = (gcnew System::Windows::Forms::Panel());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuarticB = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuarticC = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuarticE = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuarticD = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textBoxQuarticA = (gcnew System::Windows::Forms::TextBox());
			this->panelLinear->SuspendLayout();
			this->panelQuadratic->SuspendLayout();
			this->panelCube->SuspendLayout();
			this->panelQuartic->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(53, 32);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(194, 16);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Введите степень уравнения";
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
			this->label2->Size = System::Drawing::Size(155, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Реши уравнение вида:";
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
			this->panelLinear->Visible = false;
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
			this->panelQuadratic->Visible = false;
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
			this->buttonSolve->Text = L"Решить";
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
			this->labelResult->Text = L"Результат: ";
			// 
			// panelCube
			// 
			this->panelCube->Controls->Add(this->label11);
			this->panelCube->Controls->Add(this->textBoxCubeA);
			this->panelCube->Controls->Add(this->label8);
			this->panelCube->Controls->Add(this->textBoxCubeB);
			this->panelCube->Controls->Add(this->label9);
			this->panelCube->Controls->Add(this->textBoxCubeD);
			this->panelCube->Controls->Add(this->label10);
			this->panelCube->Controls->Add(this->textBoxCubeC);
			this->panelCube->Location = System::Drawing::Point(54, 232);
			this->panelCube->Name = L"panelCube";
			this->panelCube->Size = System::Drawing::Size(355, 37);
			this->panelCube->TabIndex = 10;
			this->panelCube->Visible = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(41, 14);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(45, 20);
			this->label11->TabIndex = 11;
			this->label11->Text = L"x^3 +";
			// 
			// textBoxCubeA
			// 
			this->textBoxCubeA->Location = System::Drawing::Point(5, 14);
			this->textBoxCubeA->Name = L"textBoxCubeA";
			this->textBoxCubeA->Size = System::Drawing::Size(33, 20);
			this->textBoxCubeA->TabIndex = 10;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(128, 14);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(45, 20);
			this->label8->TabIndex = 9;
			this->label8->Text = L"x^2 +";
			// 
			// textBoxCubeB
			// 
			this->textBoxCubeB->Location = System::Drawing::Point(92, 14);
			this->textBoxCubeB->Name = L"textBoxCubeB";
			this->textBoxCubeB->Size = System::Drawing::Size(33, 20);
			this->textBoxCubeB->TabIndex = 8;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(296, 14);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 20);
			this->label9->TabIndex = 7;
			this->label9->Text = L"=  0";
			// 
			// textBoxCubeD
			// 
			this->textBoxCubeD->Location = System::Drawing::Point(251, 14);
			this->textBoxCubeD->Name = L"textBoxCubeD";
			this->textBoxCubeD->Size = System::Drawing::Size(39, 20);
			this->textBoxCubeD->TabIndex = 5;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(222, 14);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(29, 20);
			this->label10->TabIndex = 6;
			this->label10->Text = L"x +";
			// 
			// textBoxCubeC
			// 
			this->textBoxCubeC->Location = System::Drawing::Point(174, 14);
			this->textBoxCubeC->Name = L"textBoxCubeC";
			this->textBoxCubeC->Size = System::Drawing::Size(45, 20);
			this->textBoxCubeC->TabIndex = 4;
			// 
			// panelQuartic
			// 
			this->panelQuartic->Controls->Add(this->label16);
			this->panelQuartic->Controls->Add(this->label12);
			this->panelQuartic->Controls->Add(this->textBoxQuarticA);
			this->panelQuartic->Controls->Add(this->textBoxQuarticB);
			this->panelQuartic->Controls->Add(this->label13);
			this->panelQuartic->Controls->Add(this->textBoxQuarticC);
			this->panelQuartic->Controls->Add(this->label14);
			this->panelQuartic->Controls->Add(this->textBoxQuarticE);
			this->panelQuartic->Controls->Add(this->label15);
			this->panelQuartic->Controls->Add(this->textBoxQuarticD);
			this->panelQuartic->Location = System::Drawing::Point(54, 286);
			this->panelQuartic->Name = L"panelQuartic";
			this->panelQuartic->Size = System::Drawing::Size(438, 37);
			this->panelQuartic->TabIndex = 12;
			this->panelQuartic->Visible = false;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(129, 14);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(45, 20);
			this->label12->TabIndex = 11;
			this->label12->Text = L"x^3 +";
			// 
			// textBoxQuarticB
			// 
			this->textBoxQuarticB->Location = System::Drawing::Point(93, 14);
			this->textBoxQuarticB->Name = L"textBoxQuarticB";
			this->textBoxQuarticB->Size = System::Drawing::Size(33, 20);
			this->textBoxQuarticB->TabIndex = 10;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(216, 14);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(45, 20);
			this->label13->TabIndex = 9;
			this->label13->Text = L"x^2 +";
			// 
			// textBoxQuarticC
			// 
			this->textBoxQuarticC->Location = System::Drawing::Point(180, 14);
			this->textBoxQuarticC->Name = L"textBoxQuarticC";
			this->textBoxQuarticC->Size = System::Drawing::Size(33, 20);
			this->textBoxQuarticC->TabIndex = 8;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(384, 14);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(35, 20);
			this->label14->TabIndex = 7;
			this->label14->Text = L"=  0";
			// 
			// textBoxQuarticE
			// 
			this->textBoxQuarticE->Location = System::Drawing::Point(339, 14);
			this->textBoxQuarticE->Name = L"textBoxQuarticE";
			this->textBoxQuarticE->Size = System::Drawing::Size(39, 20);
			this->textBoxQuarticE->TabIndex = 5;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(310, 14);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(29, 20);
			this->label15->TabIndex = 6;
			this->label15->Text = L"x +";
			// 
			// textBoxQuarticD
			// 
			this->textBoxQuarticD->Location = System::Drawing::Point(262, 14);
			this->textBoxQuarticD->Name = L"textBoxQuarticD";
			this->textBoxQuarticD->Size = System::Drawing::Size(45, 20);
			this->textBoxQuarticD->TabIndex = 4;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(41, 14);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(45, 20);
			this->label16->TabIndex = 13;
			this->label16->Text = L"x^4 +";
			// 
			// textBoxQuarticA
			// 
			this->textBoxQuarticA->Location = System::Drawing::Point(5, 14);
			this->textBoxQuarticA->Name = L"textBoxQuarticA";
			this->textBoxQuarticA->Size = System::Drawing::Size(33, 20);
			this->textBoxQuarticA->TabIndex = 12;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(979, 539);
			this->Controls->Add(this->panelQuartic);
			this->Controls->Add(this->panelCube);
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
			this->panelCube->ResumeLayout(false);
			this->panelCube->PerformLayout();
			this->panelQuartic->ResumeLayout(false);
			this->panelQuartic->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void comboBoxDegree_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
		System::Void buttonSolve_Click(System::Object^ sender, System::EventArgs^ e);
};
}

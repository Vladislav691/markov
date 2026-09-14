#pragma once

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
	private: System::Windows::Forms::TextBox^ textBoxB;
	private: System::Windows::Forms::TextBox^ textBoxA;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBoxA2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBoxC2;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBoxB2;

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
			this->panelQuadratic = (gcnew System::Windows::Forms::Panel());
			this->textBoxA = (gcnew System::Windows::Forms::TextBox());
			this->textBoxB = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxC2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxB2 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBoxA2 = (gcnew System::Windows::Forms::TextBox());
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
			this->panelLinear->Controls->Add(this->textBoxB);
			this->panelLinear->Controls->Add(this->textBoxA);
			this->panelLinear->Location = System::Drawing::Point(54, 117);
			this->panelLinear->Name = L"panelLinear";
			this->panelLinear->Size = System::Drawing::Size(282, 34);
			this->panelLinear->TabIndex = 3;
			// 
			// panelQuadratic
			// 
			this->panelQuadratic->Controls->Add(this->label7);
			this->panelQuadratic->Controls->Add(this->textBoxA2);
			this->panelQuadratic->Controls->Add(this->label5);
			this->panelQuadratic->Controls->Add(this->textBoxC2);
			this->panelQuadratic->Controls->Add(this->label6);
			this->panelQuadratic->Controls->Add(this->textBoxB2);
			this->panelQuadratic->Location = System::Drawing::Point(54, 175);
			this->panelQuadratic->Name = L"panelQuadratic";
			this->panelQuadratic->Size = System::Drawing::Size(282, 37);
			this->panelQuadratic->TabIndex = 4;
			// 
			// textBoxA
			// 
			this->textBoxA->Location = System::Drawing::Point(11, 10);
			this->textBoxA->Name = L"textBoxA";
			this->textBoxA->Size = System::Drawing::Size(33, 20);
			this->textBoxA->TabIndex = 0;
			// 
			// textBoxB
			// 
			this->textBoxB->Location = System::Drawing::Point(77, 10);
			this->textBoxB->Name = L"textBoxB";
			this->textBoxB->Size = System::Drawing::Size(33, 20);
			this->textBoxB->TabIndex = 1;
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
			// textBoxC2
			// 
			this->textBoxC2->Location = System::Drawing::Point(170, 14);
			this->textBoxC2->Name = L"textBoxC2";
			this->textBoxC2->Size = System::Drawing::Size(39, 20);
			this->textBoxC2->TabIndex = 5;
			// 
			// textBoxB2
			// 
			this->textBoxB2->Location = System::Drawing::Point(93, 14);
			this->textBoxB2->Name = L"textBoxB2";
			this->textBoxB2->Size = System::Drawing::Size(45, 20);
			this->textBoxB2->TabIndex = 4;
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
			// textBoxA2
			// 
			this->textBoxA2->Location = System::Drawing::Point(11, 14);
			this->textBoxA2->Name = L"textBoxA2";
			this->textBoxA2->Size = System::Drawing::Size(33, 20);
			this->textBoxA2->TabIndex = 8;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(979, 539);
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
	};
}

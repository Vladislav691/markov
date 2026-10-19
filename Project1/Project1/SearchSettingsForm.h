#pragma once

namespace Project1
{

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SearchSettingsForm : public System::Windows::Forms::Form
    {
    public:
        SearchSettingsForm(void)
        {
            InitializeComponent();
            SetValues(-10, 10, 1e-6);
        }

        void SetValues(double left, double right, double accuracy);

        property double LeftBoundary
        {
            double get()
            {
                return leftBoundary;
            }
        }

        property double RightBoundary
        {
            double get()
            {
                return rightBoundary;
            }
        }

        property double Accuracy
        {
            double get()
            {
                return accuracyValue;
            }
        }

    private:
        double leftBoundary;
        double rightBoundary;
        double accuracyValue;
        double ReadNumber(System::Windows::Forms::TextBox^ field, System::String^ caption);

    protected:
        ~SearchSettingsForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ label1;

        System::Windows::Forms::TextBox^ textBoxLeft;

        System::Windows::Forms::TextBox^ textBoxRight;

        System::Windows::Forms::Label^ label2;

        System::Windows::Forms::TextBox^ textBoxAccuracy;

        System::Windows::Forms::Label^ label3;

        System::Windows::Forms::Button^ buttonApply;

        System::Windows::Forms::Button^ buttonCancel;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->textBoxLeft = (gcnew System::Windows::Forms::TextBox());
            this->textBoxRight = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->textBoxAccuracy = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->buttonApply = (gcnew System::Windows::Forms::Button());
            this->buttonCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif",
                                                              9.75F,
                                                              System::Drawing::FontStyle::Regular,
                                                              System::Drawing::GraphicsUnit::Point,
                                                              static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(12, 26);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(107, 16);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Левая граница:";
            this->textBoxLeft->Location = System::Drawing::Point(131, 22);
            this->textBoxLeft->Name = L"textBoxLeft";
            this->textBoxLeft->Size = System::Drawing::Size(233, 20);
            this->textBoxLeft->TabIndex = 1;
            this->textBoxRight->Location = System::Drawing::Point(131, 64);
            this->textBoxRight->Name = L"textBoxRight";
            this->textBoxRight->Size = System::Drawing::Size(233, 20);
            this->textBoxRight->TabIndex = 3;
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif",
                                                              9.75F,
                                                              System::Drawing::FontStyle::Regular,
                                                              System::Drawing::GraphicsUnit::Point,
                                                              static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(12, 68);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(116, 16);
            this->label2->TabIndex = 2;
            this->label2->Text = L"Правая граница:";
            this->textBoxAccuracy->Location = System::Drawing::Point(131, 106);
            this->textBoxAccuracy->Name = L"textBoxAccuracy";
            this->textBoxAccuracy->Size = System::Drawing::Size(233, 20);
            this->textBoxAccuracy->TabIndex = 5;
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif",
                                                              9.75F,
                                                              System::Drawing::FontStyle::Regular,
                                                              System::Drawing::GraphicsUnit::Point,
                                                              static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(12, 110);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(72, 16);
            this->label3->TabIndex = 4;
            this->label3->Text = L"Точность:";
            this->buttonApply->BackColor = System::Drawing::Color::DarkCyan;
            this->buttonApply->Location = System::Drawing::Point(122, 156);
            this->buttonApply->Name = L"buttonApply";
            this->buttonApply->Size = System::Drawing::Size(118, 29);
            this->buttonApply->TabIndex = 6;
            this->buttonApply->Text = L"Применить";
            this->buttonApply->UseVisualStyleBackColor = false;
            this->buttonApply->Click +=
                gcnew System::EventHandler(this, &SearchSettingsForm::buttonApply_Click);
            this->buttonCancel->Location = System::Drawing::Point(246, 156);
            this->buttonCancel->Name = L"buttonCancel";
            this->buttonCancel->Size = System::Drawing::Size(118, 29);
            this->buttonCancel->TabIndex = 7;
            this->buttonCancel->Text = L"Отмена";
            this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->buttonCancel->UseVisualStyleBackColor = true;
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(385, 195);
            this->Controls->Add(this->buttonCancel);
            this->Controls->Add(this->buttonApply);
            this->Controls->Add(this->textBoxAccuracy);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->textBoxRight);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->textBoxLeft);
            this->Controls->Add(this->label1);
            this->AcceptButton = this->buttonApply;
            this->CancelButton = this->buttonCancel;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"SearchSettingsForm";
            this->Text = L"Настройки численного поиска";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

#pragma endregion
    private:
        System::Void buttonApply_Click(System::Object ^ sender, System::EventArgs ^ e);
    };
}

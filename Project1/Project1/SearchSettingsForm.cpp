#include "SearchSettingsForm.h"
#include "SearchSettings.h"
System::Void Project1::SearchSettingsForm::buttonApply_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        PolynomialSolver::SearchSettings settings;

        if (!System::Double::TryParse(textBoxLeft->Text, settings.left))
        {
            throw gcnew System::ArgumentException(L"Введите число в поле «Левая граница».");
        }
        if (!System::Double::TryParse(textBoxRight->Text, settings.right))
        {
            throw gcnew System::ArgumentException(L"Введите число в поле «Правая граница».");
        }
        if (!System::Double::TryParse(textBoxAccuracy->Text, settings.accuracy))
        {
            throw gcnew System::ArgumentException(L"Введите число в поле «Точность».");
        }

        settings.Validate();
        this->DialogResult = System::Windows::Forms::DialogResult::OK;
    }
    catch (System::Exception ^ error)
    {
        System::Windows::Forms::MessageBox::Show(error->Message, L"Ошибка ввода");
    }
}

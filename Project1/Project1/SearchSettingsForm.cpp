#include "SearchSettingsForm.h"
#include "SearchSettings.h"

namespace Project1
{
    using namespace System;
    using namespace System::Globalization;
    using namespace System::Windows::Forms;

    void SearchSettingsForm::SetValues(double left, double right, double accuracy)
    {
        leftBoundary = left;
        rightBoundary = right;
        accuracyValue = accuracy;
        textBoxLeft->Text = left.ToString(L"G", CultureInfo::CurrentCulture);
        textBoxRight->Text = right.ToString(L"G", CultureInfo::CurrentCulture);
        textBoxAccuracy->Text = accuracy.ToString(L"0.############", CultureInfo::CurrentCulture);
    }

    double SearchSettingsForm::ReadNumber(TextBox^ field, String^ caption)
    {
        double value;
        String^ text = field->Text->Trim()->Replace(L',', L'.');
        if (!Double::TryParse(text, NumberStyles::Float, CultureInfo::InvariantCulture, value))
        {
            throw gcnew ArgumentException(L"Введите число в поле «" + caption + L"».");
        }
        return value;
    }

    System::Void SearchSettingsForm::buttonApply_Click(System::Object^, System::EventArgs^)
    {
        try
        {
            PolynomialSolver::SearchSettings settings;
            settings.left = ReadNumber(textBoxLeft, L"Левая граница");
            settings.right = ReadNumber(textBoxRight, L"Правая граница");
            settings.accuracy = ReadNumber(textBoxAccuracy, L"Точность");
            settings.Validate();
            const double minimumAccuracy = 0.000000000001;
            if (settings.accuracy < minimumAccuracy)
            {
                throw gcnew ArgumentException(L"Минимальная погрешность: 0,000000000001.");
            }

            leftBoundary = settings.left;
            rightBoundary = settings.right;
            accuracyValue = settings.accuracy;
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
        }
        catch (System::Exception^ error)
        {
            MessageBox::Show(this, error->Message, L"Ошибка ввода");
        }
    }
}

#include "MyForm.h"
#include <clocale>

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
    setlocale(LC_ALL, "Russian");
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Application::Run(gcnew Project1::MyForm());

    return 0;
}
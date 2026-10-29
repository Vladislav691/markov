#pragma once

#include "GraphPanel.h"

namespace Project1
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class GraphForm : public Form
    {
    public:
        GraphForm(cli::array<double>^ coefficients, cli::array<double>^ roots)
        {
            Name = L"GraphForm";
            Text = L"График полинома";
            Size = Drawing::Size(900, 600);
            MinimumSize = Drawing::Size(500, 400);
            StartPosition = FormStartPosition::CenterParent;
            PolynomialSolver::UI::GraphPanel^ graph = gcnew PolynomialSolver::UI::GraphPanel();
            graph->Name = L"graphPanel";
            graph->Dock = DockStyle::Fill;
            Controls->Add(graph);
            graph->SetPolynomial(coefficients, roots);
        }
    };
}
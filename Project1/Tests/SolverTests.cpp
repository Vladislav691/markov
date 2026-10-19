#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "../Project1/BisectionSolver.h"
#include "../Project1/CubeEquation.h"
#include "../Project1/LinearEquation.h"
#include "../Project1/MyForm.h"
#include "../Project1/QuadraticEquation.h"
#include "../Project1/QuarticEquation.h"

using namespace std;
using namespace PolynomialSolver;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

int HeaderCompileCheck();

namespace
{
    int passed = 0;
    int failed = 0;

    void Check(bool condition, const char* message)
    {
        if (!condition)
        {
            throw gcnew System::Exception(gcnew String(message));
        }
    }

    void Test(const char* name, const function<void()>& action)
    {
        try
        {
            action();
            ++passed;
            cout << "PASS " << name << "\n";
        }
        catch (System::Exception^ error)
        {
            ++failed;
            Console::WriteLine("FAIL {0}: {1}", gcnew String(name), error->Message);
        }
    }

    void Reject(const function<void()>& action)
    {
        bool rejected = false;
        try
        {
            action();
        }
        catch (System::Exception^)
        {
            rejected = true;
        }
        Check(rejected, "invalid input accepted");
    }

    void Roots(const EquationSolver& solver,
               const vector<double>& coefficients,
               const vector<Complex>& expected,
               double tolerance = 1e-6)
    {
        Polynomial polynomial(coefficients);
        Solution solution = solver.Solve(polynomial);
        VerifySolution(polynomial, solution);
        Check(solution.verified, "substitution verification failed");
        Check(solution.roots.size() == expected.size(), "wrong root count");
        auto actual = solution.roots;
        for (Complex root : expected)
        {
            auto nearest = min_element(actual.begin(),
                                       actual.end(),
                                       [root](Complex a, Complex b)
                                       {
                                           return abs(a - root) < abs(b - root);
                                       });
            Check(nearest != actual.end() && abs(*nearest - root) <= tolerance * (1 + abs(root)),
                  "wrong root value");
            Check(polynomial.RelativeResidual(*nearest) <= 1e-6, "substitution failed");
            actual.erase(nearest);
        }
    }

    SearchSettings Settings(double left, double right, double step, double accuracy = 1e-9)
    {
        SearchSettings settings;
        settings.left = left;
        settings.right = right;
        settings.step = step;
        settings.accuracy = accuracy;
        return settings;
    }

    Control^ Find(Control^ parent, String^ name)
    {
        if (parent->Name == name)
        {
            return parent;
        }
        for each (Control^ child in parent->Controls)
        {
            Control^ found = Find(child, name);
            if (found != nullptr)
            {
                return found;
            }
        }
        return nullptr;
    }

    TextBox^ Field(Form^ form, String^ name)
    {
        return safe_cast<TextBox^>(Find(form, name));
    }

    ComboBox^ Choice(Form^ form, String^ name)
    {
        return safe_cast<ComboBox^>(Find(form, name));
    }

    void SetCoefficients(Form^ form, String^ prefix, cli::array<String^>^ values)
    {
        for (int i = 0; i < values->Length; ++i)
        {
            Field(form, L"textBox" + prefix + gcnew String(static_cast<wchar_t>(L'A' + i), 1))->Text =
                values[i];
        }
    }

    void Click(Form^ form, String^ name)
    {
        safe_cast<Button^>(Find(form, name))->PerformClick();
        Application::DoEvents();
    }

    ref class SettingsDialogAction
    {
    public:
        Timer^ timer;
        String^ left;
        String^ right;
        String^ accuracy;
        String^ initialLeft;
        String^ initialAccuracy;
        bool cancel;

        SettingsDialogAction(String^ leftValue, String^ rightValue, String^ accuracyValue, bool cancelValue)
        {
            left = leftValue;
            right = rightValue;
            accuracy = accuracyValue;
            cancel = cancelValue;
            timer = gcnew Timer();
            timer->Interval = 50;
            timer->Tick += gcnew EventHandler(this, &SettingsDialogAction::OnTick);
        }

        void OnTick(Object^, EventArgs^)
        {
            Form^ dialog = Application::OpenForms[L"SearchSettingsForm"];
            if (dialog == nullptr)
            {
                return;
            }
            timer->Stop();
            initialLeft = Field(dialog, L"textBoxLeft")->Text;
            initialAccuracy = Field(dialog, L"textBoxAccuracy")->Text;
            Field(dialog, L"textBoxLeft")->Text = left;
            Field(dialog, L"textBoxRight")->Text = right;
            Field(dialog, L"textBoxAccuracy")->Text = accuracy;
            if (cancel)
            {
                Click(dialog, L"buttonCancel");
            }
            else
            {
                Click(dialog, L"buttonApply");
            }
        }
    };

    SettingsDialogAction^ EditSettings(Form^ form, String^ left, String^ right, String^ accuracy, bool cancel)
    {
        SettingsDialogAction^ action = gcnew SettingsDialogAction(left, right, accuracy, cancel);
        try
        {
            action->timer->Start();
            Click(form, L"buttonSearchSettings");
        }
        finally
        {
            delete action->timer;
        }
        return action;
    }
    void UIFlow()
    {
        Project1::MyForm^ form = gcnew Project1::MyForm();
        try
        {
            form->Show();
            Application::DoEvents();
            auto degree = Choice(form, L"comboBoxDegree");
            auto method = Choice(form, L"comboBoxMethod");
            auto result = Find(form, L"labelResult");
            Check(!method->Visible && !Find(form, L"panelInterval")->Visible, "linear visibility");
            SetCoefficients(form, L"Linear", gcnew cli::array<String^>{L"1e-300", L"1e300"});
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"double") && degree->Enabled, "managed overflow not handled");
            SetCoefficients(form, L"Linear", gcnew cli::array<String^>{L"2", L"-4"});
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"x1 = 2"), "linear UI result");
            Check(!degree->Enabled && Field(form, L"textBoxLinearA")->ReadOnly, "linear not locked");
            Click(form, L"buttonReset");
            Check(degree->Enabled && !Field(form, L"textBoxLinearA")->ReadOnly, "reset not unlocked");
            degree->SelectedIndex = 1;
            Check(!Find(form, L"panelInterval")->Visible && !method->Visible, "quadratic settings visible");
            SetCoefficients(form, L"Quadratic", gcnew cli::array<String^>{L"1", L"0", L"1"});
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"i"), "complex UI result missing");
            Click(form, L"buttonReset");
            degree->SelectedIndex = 2;
            Check(method->Visible && !Find(form, L"panelInterval")->Visible, "cubic method missing");
            SetCoefficients(form, L"Cube", gcnew cli::array<String^>{L"1", L"-6", L"11", L"-6"});
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"x3") && !method->Enabled, "Cardano UI or lock failed");
            Click(form, L"buttonReset");
            method->SelectedIndex = 1;
            Check(Find(form, L"panelInterval")->Visible, "numerical fields hidden");
            Check(Find(form, L"textBoxSearchStep") == nullptr, "step input still exists");
            Check(Find(form, L"textBoxIntervalLeft") == nullptr, "main settings input still exists");
            auto defaults = EditSettings(form, L"0", L"4", L"1e-9", false);
            Check(defaults->initialAccuracy->Replace(L',', L'.') == L"0.000001",
                  "default accuracy not displayed as decimal");
            EditSettings(form, L"0", L"4", L"0.000000000001", false);
            auto minimum = EditSettings(form, L"0", L"4", L"1e-9", false);
            Check(minimum->initialAccuracy->Replace(L',', L'.') == L"0.000000000001",
                  "minimum accuracy rounded to zero");
            auto cancelled = EditSettings(form, L"20", L"30", L"0,5", true);
            Check(cancelled->initialLeft == L"0", "saved settings not loaded");
            auto reopened = EditSettings(form, L"20", L"30", L"0.5", true);
            Check(reopened->initialLeft == L"0", "cancel changed saved settings");
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"x3"), "numerical multiple roots missing");
            Check(!Find(form, L"buttonSearchSettings")->Enabled, "settings not locked");
            String^ directory = IO::Path::Combine(AppDomain::CurrentDomain->BaseDirectory, L"previews");
            IO::Directory::CreateDirectory(directory);
            Bitmap^ bitmap = gcnew Bitmap(form->Width, form->Height);
            form->DrawToBitmap(bitmap, Rectangle(0, 0, bitmap->Width, bitmap->Height));
            bitmap->Save(IO::Path::Combine(directory, L"cubic-numerical.png"));
            delete bitmap;
            Click(form, L"buttonReset");
            Check(Find(form, L"buttonSearchSettings")->Enabled, "settings not unlocked");
            method->SelectedIndex = 0;
            degree->SelectedIndex = 3;
            SetCoefficients(form, L"Quartic", gcnew cli::array<String^>{L"1", L"0", L"0", L"1", L"1"});
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"x4") && result->Text->Contains(L"i"), "Ferrari UI failed");
            bitmap = gcnew Bitmap(form->Width, form->Height);
            form->DrawToBitmap(bitmap, Rectangle(0, 0, bitmap->Width, bitmap->Height));
            bitmap->Save(IO::Path::Combine(directory, L"quartic-analytical.png"));
            delete bitmap;
            Click(form, L"buttonReset");
            form->Size = Drawing::Size(800, 600);
            degree->SelectedIndex = 4;
            Check(!method->Visible && Find(form, L"panelInterval")->Visible, "fifth visibility");
            SetCoefficients(form, L"Fifth", gcnew cli::array<String^>{L"1", L"0", L"-5", L"0", L"4", L"0"});
            EditSettings(form, L"-3", L"3", L"0,000000001", false);
            Click(form, L"buttonSolve");
            Check(result->Text->Contains(L"x5"), "fifth roots missing");
            bitmap = gcnew Bitmap(form->Width, form->Height);
            form->DrawToBitmap(bitmap, Rectangle(0, 0, bitmap->Width, bitmap->Height));
            bitmap->Save(IO::Path::Combine(directory, L"fifth-minimum.png"));
            delete bitmap;
        }
        finally
        {
            form->Close();
            delete form;
        }
    }
}
[STAThread]
int main()
{
    Application::EnableVisualStyles();
    Test("Horner real and complex",
         []
         {
             Polynomial p({1, -5, 6});
             Check(p.Evaluate(2.0) == 0 && abs(p.Evaluate(Complex(0, 1)) - Complex(5, -5)) < 1e-12, "Horner");
         });
    Test("linear root",
         []
         {
             Roots(LinearEquation(), {2, -4}, {2});
         });
    Test("linear no solutions",
         []
         {
             Check(LinearEquation().Solve(Polynomial({0, 1})).kind == SolutionKind::None, "kind");
         });
    Test("linear infinite solutions",
         []
         {
             Check(LinearEquation().Solve(Polynomial({0, 0})).kind == SolutionKind::Infinite, "kind");
         });
    Test("quadratic two real",
         []
         {
             Roots(QuadraticEquation(), {1, -5, 6}, {2, 3});
         });
    Test("quadratic repeated",
         []
         {
             Roots(QuadraticEquation(), {1, -2, 1}, {1, 1});
         });
    Test("quadratic complex",
         []
         {
             Roots(QuadraticEquation(), {1, 0, 1}, {Complex(0, 1), Complex(0, -1)});
         });
    Test("quadratic zero root",
         []
         {
             Roots(QuadraticEquation(), {1, -2, 0}, {0, 2});
         });
    Test("quadratic cancellation",
         []
         {
             Roots(QuadraticEquation(), {1, -1e8, 1}, {1e8, 1e-8});
         });
    Test("quadratic coefficient scale",
         []
         {
             Roots(QuadraticEquation(), {1e200, -5e200, 6e200}, {2, 3});
         });
    Test("Cardano three real",
         []
         {
             Roots(CubeEquation(), {1, -6, 11, -6}, {1, 2, 3});
         });
    Test("Cardano complex pair",
         []
         {
             Roots(CubeEquation(),
                   {1, 0, 0, -1},
                   {1, Complex(-0.5, sqrt(3.0) / 2), Complex(-0.5, -sqrt(3.0) / 2)});
         });
    Test("Cardano triple root",
         []
         {
             Roots(CubeEquation(), {1, -3, 3, -1}, {1, 1, 1});
         });
    Test("Cardano double root",
         []
         {
             Roots(CubeEquation(), {1, 0, -3, 2}, {-2, 1, 1});
         });
    Test("Cardano zero roots",
         []
         {
             Roots(CubeEquation(), {1, 0, -1, 0}, {-1, 0, 1});
             Roots(CubeEquation(), {1, 0, 0, 0}, {0, 0, 0});
         });
    Test("Ferrari four real",
         []
         {
             Roots(QuarticEquation(), {1, -10, 35, -50, 24}, {1, 2, 3, 4});
         });
    Test("Ferrari nonzero q",
         []
         {
             Roots(QuarticEquation(), {1, -7, 5, 31, -30}, {-2, 1, 3, 5});
         });
    Test("Ferrari complex biquadratic",
         []
         {
             Roots(QuarticEquation(),
                   {1, 0, 5, 0, 4},
                   {Complex(0, 1), Complex(0, -1), Complex(0, 2), Complex(0, -2)});
         });
    Test("Ferrari quadruple root",
         []
         {
             Roots(QuarticEquation(), {1, -4, 6, -4, 1}, {1, 1, 1, 1});
         });
    Test("Ferrari mixed roots",
         []
         {
             Roots(QuarticEquation(), {1, -1, -1, -1, -2}, {-1, 2, Complex(0, 1), Complex(0, -1)});
         });
    Test("Ferrari zero polynomial powers",
         []
         {
             Roots(QuarticEquation(), {1, 0, 0, 0, 0}, {0, 0, 0, 0});
         });
    Test("bisection all cubic roots",
         []
         {
             Roots(BisectionSolver(Settings(0, 4, 0.3)), {1, -6, 11, -6}, {1, 2, 3});
         });
    Test("bisection fifth five roots",
         []
         {
             Roots(BisectionSolver(Settings(-3, 3, 0.23)), {1, 0, -5, 0, 4, 0}, {-2, -1, 0, 1, 2});
         });
    Test("bisection same signs at full bounds",
         []
         {
             Roots(BisectionSolver(Settings(-3, 3, 0.4)), {1, 0, -4}, {-2, 2});
         });
    Test("bisection endpoint and duplicate node",
         []
         {
             Roots(BisectionSolver(Settings(-1, 1, 0.5)), {1, 0, -1, 0}, {-1, 0, 1});
         });
    Test("bisection last partial interval",
         []
         {
             Roots(BisectionSolver(Settings(0, 1, 0.3)), {1, -0.95}, {0.95});
         });
    Test("bisection step larger than range",
         []
         {
             Roots(BisectionSolver(Settings(0, 2, 100)), {1, -1}, {1});
         });
    Test("bisection no real roots",
         []
         {
             Check(BisectionSolver(Settings(-2, 2, 0.1)).Solve(Polynomial({1, 0, 1})).kind ==
                       SolutionKind::None,
                   "kind");
         });
    Test("bisection even root limitation",
         []
         {
             Check(BisectionSolver(Settings(-1, 1, 0.3)).Solve(Polynomial({1, 0, 0})).roots.empty(),
                   "even root unexpectedly found");
         });
    Test("bisection accuracy in x",
         []
         {
             const double root =
                 BisectionSolver(Settings(1, 2, 1, 1e-7)).Solve(Polynomial({1, 0, -2})).roots[0].real();
             Check(abs(root - sqrt(2.0)) <= 1e-7, "accuracy");
         });
    Test("invalid coefficients",
         []
         {
             Reject(
                 []
                 {
                     Polynomial p({0, 1, 2});
                 });
             Reject(
                 []
                 {
                     Polynomial p({1, numeric_limits<double>::infinity()});
                 });
             Reject(
                 []
                 {
                     Polynomial p({1, numeric_limits<double>::quiet_NaN()});
                 });
             Reject(
                 []
                 {
                     Polynomial p({1});
                 });
         });
    Test("invalid numerical settings",
         []
         {
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(1, 1, 0.1));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(2, 1, 0.1));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, 0));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, -1));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, 0.1, 0));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, 0.1, -1));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, 1e-9));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, numeric_limits<double>::quiet_NaN()));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, numeric_limits<double>::infinity(), 1));
                 });
         });
    Test("overflow is reported",
         []
         {
             Reject(
                 []
                 {
                     BisectionSolver(Settings(1e100, 2e100, 1e100)).Solve(Polynomial({1e300, 1, 1}));
                 });
         });
    Test("wrong solver degree",
         []
         {
             Reject(
                 []
                 {
                     LinearEquation().Solve(Polynomial({1, 2, 3}));
                 });
         });
    Test("substitution detects invalid root",
         []
         {
             Polynomial p({1, 0, -1});
             Solution s;
             s.roots = {2};
             VerifySolution(p, s);
             Check(!s.verified, "false verification");
         });
    Test("generated quartics preserve all roots",
         []
         {
             mt19937 engine(42);
             uniform_int_distribution<int> pick(-5, 5);
             for (int test = 0; test < 100; ++test)
             {
                 vector<double> c{1};
                 vector<Complex> roots;
                 for (int i = 0; i < 4; ++i)
                 {
                     double root = pick(engine);
                     roots.emplace_back(root);
                     vector<double> next(c.size() + 1, 0);
                     for (size_t j = 0; j < c.size(); ++j)
                     {
                         next[j] += c[j];
                         next[j + 1] -= root * c[j];
                     }
                     c = next;
                 }
                 Roots(QuarticEquation(), c, roots, 1e-4);
             }
         });
    Test("generated Cardano roots",
         []
         {
             mt19937 engine(109);
             uniform_real_distribution<double> pick(-5, 5);
             for (int test = 0; test < 100; ++test)
             {
                 double real = pick(engine);
                 double a = pick(engine);
                 double b = 0.5 + abs(pick(engine));
                 Roots(CubeEquation(),
                       {1, -2 * a - real, a * a + b * b + 2 * a * real, -real * (a * a + b * b)},
                       {real, Complex(a, b), Complex(a, -b)},
                       1e-6);
             }
         });
    Test("generated Ferrari complex pairs",
         []
         {
             mt19937 engine(110);
             uniform_real_distribution<double> pick(-5, 5);
             for (int test = 0; test < 100; ++test)
             {
                 double a = pick(engine);
                 double b = 0.5 + abs(pick(engine));
                 double c = pick(engine);
                 double d = 0.5 + abs(pick(engine));
                 const double first = a * a + b * b;
                 const double second = c * c + d * d;
                 Roots(QuarticEquation(),
                       {1,
                        -2 * (a + c),
                        first + second + 4 * a * c,
                        -2 * (a * second + c * first),
                        first * second},
                       {Complex(a, b), Complex(a, -b), Complex(c, d), Complex(c, -d)},
                       1e-6);
             }
         });
    Test("bisection insufficient precision is reported",
         []
         {
             Reject(
                 []
                 {
                     BisectionSolver(Settings(1, 2, 1, 1e-30)).Solve(Polynomial({1, 0, -2}));
                 });
         });
    Test("bisection coarse accuracy warns on substitution",
         []
         {
             Polynomial polynomial({1, -0.1});
             Solution result = BisectionSolver(Settings(0, 2, 2, 1)).Solve(polynomial);
             VerifySolution(polynomial, result);
             Check(!result.verified && result.roots.size() == 1, "coarse root did not warn");
         });
    Test("nonfinite settings rejected",
         []
         {
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, 0.1, numeric_limits<double>::infinity()));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(numeric_limits<double>::quiet_NaN(), 1, 1));
                 });
             Reject(
                 []
                 {
                     BisectionSolver s(Settings(0, 1, numeric_limits<double>::infinity()));
                 });
         });
    Test("verification rejects nonfinite roots",
         []
         {
             Reject(
                 []
                 {
                     Polynomial polynomial({1, -1});
                     Solution result;
                     result.roots.push_back(numeric_limits<double>::infinity());
                     VerifySolution(polynomial, result);
                 });

             Reject(
                 []
                 {
                     Polynomial polynomial({1, -1});
                     Solution result;
                     result.roots.push_back(numeric_limits<double>::quiet_NaN());
                     VerifySolution(polynomial, result);
                 });
         });
    Test("headers included in two translation units",
         []
         {
             Check(HeaderCompileCheck() == 1, "header linkage failed");
         });
    Test("form methods, results, reset, input and layouts", UIFlow);
    cout << passed << " passed, " << failed << " failed\n";
    if (failed == 0)
    {
        return 0;
    }

    return 1;
}

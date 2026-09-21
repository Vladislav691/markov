#pragma once

#include <cmath>
#include <complex>

using namespace System;
using namespace std;

public ref class QuarticEquation
{
private:

    complex<double> solveCubicResolvent(
        complex<double> A,
        complex<double> B,
        complex<double> C,
        complex<double> D)
    {
        complex<double> p =
            (3.0 * A * C - B * B) /
            (3.0 * A * A);

        complex<double> q =
            (2.0 * B * B * B
                - 9.0 * A * B * C
                + 27.0 * A * A * D) /
            (27.0 * A * A * A);

        complex<double> delta =
            (q * q / 4.0) +
            (p * p * p / 27.0);

        complex<double> r1 =
            -q / 2.0 + sqrt(delta);

        complex<double> r2 =
            -q / 2.0 - sqrt(delta);

        complex<double> u =
            pow(r1, 1.0 / 3.0);

        complex<double> v =
            pow(r2, 1.0 / 3.0);

        return u + v - (B / (3.0 * A));
    }


public:

    String^ solveQuarticFerrari(
        double a,
        double b,
        double c,
        double d,
        double e)
    {
        if (a == 0)
        {
            System::Windows::Forms::MessageBox::Show(
                "Коэффициент 'a' не должен быть равен 0.",
                "Ошибка",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Error
            );

            return nullptr;
        }

        double p =
            (8.0 * a * c - 3.0 * b * b) /
            (8.0 * a * a);

        double q =
            (8.0 * a * a * d
                - 4.0 * a * b * c
                + b * b * b) /
            (8.0 * a * a * a);

        double r =
            (16.0 * a * b * b * c
                - 64.0 * a * a * b * d
                - 3.0 * b * b * b * b
                + 256.0 * a * a * a * e) /
            (256.0 * a * a * a * a);

        double shift = b / (4.0 * a);

        complex<double> roots[4];

        if (abs(q) < 1e-12)
        {
            complex<double> disc =
                p * p - 4.0 * r;

            complex<double> y2_1 =
                (-p + sqrt(disc)) / 2.0;

            complex<double> y2_2 =
                (-p - sqrt(disc)) / 2.0;

            roots[0] = sqrt(y2_1) - shift;
            roots[1] = -sqrt(y2_1) - shift;
            roots[2] = sqrt(y2_2) - shift;
            roots[3] = -sqrt(y2_2) - shift;
        }
        else
        {
            complex<double> s =
                solveCubicResolvent(
                    8.0,
                    -4.0 * p,
                    -8.0 * r,
                    4.0 * p * r - q * q
                );

            complex<double> sqrt_2s_p =
                sqrt(2.0 * s - p);

            complex<double> q_div_2s =
                q / (2.0 * sqrt_2s_p);

            complex<double> k1_b =
                sqrt_2s_p;

            complex<double> k1_c =
                s - q_div_2s;

            complex<double> disc1 =
                k1_b * k1_b - 4.0 * k1_c;

            roots[0] =
                (-k1_b + sqrt(disc1)) / 2.0 - shift;

            roots[1] =
                (-k1_b - sqrt(disc1)) / 2.0 - shift;


            complex<double> k2_b =
                -sqrt_2s_p;

            complex<double> k2_c =
                s + q_div_2s;

            complex<double> disc2 =
                k2_b * k2_b - 4.0 * k2_c;

            roots[2] =
                (-k2_b + sqrt(disc2)) / 2.0 - shift;

            roots[3] =
                (-k2_b - sqrt(disc2)) / 2.0 - shift;
        }

        String^ result = String::Format(
            "Корни уравнения:\n"
            "x1 = {0:F4} + ({1:F4})i\n"
            "x2 = {2:F4} + ({3:F4})i\n"
            "x3 = {4:F4} + ({5:F4})i\n"
            "x4 = {6:F4} + ({7:F4})i",

            roots[0].real(), roots[0].imag(),
            roots[1].real(), roots[1].imag(),
            roots[2].real(), roots[2].imag(),
            roots[3].real(), roots[3].imag()
        );

        return result;
    }
};
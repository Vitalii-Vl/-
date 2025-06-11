#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * @brief Ввод положительного целого числа (>0)
 * @param prompt – строка-ввода
 * @return число-ввода (>0)
 */
int inputInt(const string& prompt);

/**
 * @brief Ввод положительного вещественное число (>0)
 * @param prompt – строка-ввода
 * @return число-ввода (>0)
 */
double inputDouble(const string& prompt);

/**
 * @brief вычисляет сумму членов последовательности со 2-го по (n + 1)-й
 * @param n количество суммируемых членов (n ≥ 1)
 * @return S = a_2 + … + a_{n+1}
 */
double sumN(int n);

/**
 * @brief вычисляет сумму всех членов, модуль которых не меньше eps
 * @param eps положительный порог отсечки (eps > 0)
 * @return S_eps — искомая сумма
 */
double sumByEps(double eps);

/**
 * @brief Точка входа в программу
 * @return 0 при успешной работе, 1 — если ввод некорректен
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    int n = inputInt("n (>=1): ");
    double eps = inputDouble("n>0): ");
    cout << fixed << setprecision(10);
    cout << "\nS = " << sumN(n) << '\n';
    cout << "S_eps = " << sumByEps(eps) << '\n';
    return 0;
}

int inputInt(const string& prompt)
{
    int tmp = 0;
    cout << prompt;
    cin >> tmp;
    if (cin.fail() || tmp < 1)
    {
        cout << "Ошибка!\n";
        abort();
    }
    return tmp;
}

double inputDouble(const string& prompt)
{
    double tmp = 0.1;
    cout << prompt;
    cin >> tmp;
    if (cin.fail() || tmp <= 0.0)
    {
        cout << "Ошибка!\n";
        abort();
    }
    return tmp;
}

double sumN(int n)
{
    double sum = 0.0;
    double a_k = -1.0;

   for (int k = 1; k < n; ++k)
        a_k *= (-1.0) / (k * k);
        sum += a_k;
    }
    return sum;
}

double sumByEps(double eps)
{
    double sum = 0.0;
    double a_k = -1.0;
    int k = 1;

    while (fabs(a_k) >= eps) {
        sum += a_k;
        a_k *= (-1.0) / (k * k);
        ++k;
    }
    return sum;
}

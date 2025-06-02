#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * @brief вычисляет сумму первых n членов последовательности через рекуррентное выражение
 * @param n – количество членов (>=1)
 * @return S_n — сумма первых n членов
 */
double sumFirstN(int n);

/**
 * @brief вычисляет сумму всех членов, модуль которых не меньше eps, через рекуррентное выражение
 * @param eps – положительный порог отсечки
 * @return S_eps — искомую сумму
 */
double sumByEps(double eps);

/**
 * @brief Точка входа в программу
 * @return код завершения программы (0 — успех)
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    double eps;

    cout << "n (>=1): ";
    while (!(cin >> n) || n < 1) {
        cout << "Ошибка. Повторите ввод n: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "eps (>0): ";
    while (!(cin >> eps) || eps <= 0.0) {
        cout << "Ошибка. Повторите ввод eps: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << fixed << setprecision(10);
    cout << "\nS_n = " << sumFirstN(n) << '\n';
    cout << "S_eps = " << sumByEps(eps) << '\n';
    return 0;
}

double sumFirstN(int n)
{
    double sum = 0.0;
    double a_k = -1.0;

    for (int k = 1; k <= n; ++k) {
        if (k > 1) {
            a_k = a_k * (-1.0) / (k * k);
        }
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
        ++k;
        a_k = a_k * (-1.0) / (k * k);
    }

    return sum;
}

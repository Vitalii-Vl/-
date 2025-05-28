#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief вычисляет факториал числа k рекурсивно
 * @param k - неотрицательное целое число
 * @return k! в виде long long
 */
long long factorial(int k);

/**
 * @brief вычисляет k-й член последовательности
 * @param k - порядковый номер члена (>= 1)
 * @return значение a_k
 */
double term(int k);

/**
 * @brief вычисляет сумму первых n членов последовательности рекурсивно
 * @param n - количество членов (>= 1)
 * @return S_n — сумму первых n членов
 */
double sumFirstN(int n);

/**
 * @brief вспомогательная рекурсивная функция для sumByEps
 * @param eps - порог отсечки
 * @param k - текущий номер члена
 * @return частичная сумма от a_k до конца
 */
double sumByEpsRec(double eps, int k);

/**
 * @brief вычисляет сумму всех членов, модуль которых не меньше eps рекурсивно
 * @param eps - положительный порог отсечки
 * @return S_eps — искомую сумму
 */
double sumByEps(double eps);

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

    cout.precision(10);
    cout << "\nS_n = " << sumFirstN(n) << '\n';
    cout << "S_eps = " << sumByEps(eps) << '\n';
    return 0;
}

long long factorial(int k)
{
    return (k <= 1) ? 1 : k * factorial(k - 1);
}

double term(int k)
{
    long long f = factorial(k);
    double sign = (k % 2 ? -1.0 : 1.0);
    return sign / (f * f);
}

double sumFirstN(int n)
{
    return (n == 1) ? term(1) : sumFirstN(n - 1) + term(n);
}

double sumByEpsRec(double eps, int k)
{
    double a = term(k);
    return (fabs(a) < eps) ? 0.0 : a + sumByEpsRec(eps, k + 1);
}

double sumByEps(double eps)
{
    return sumByEpsRec(eps, 1);
}

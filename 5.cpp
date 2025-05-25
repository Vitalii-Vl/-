#include <iostream>
#include <math.h>

/*
* @brief вычисляет факториал числа k итеративно
* @param k - неотрицательное целое число
* @return k!в виде long long
*/
long long factorial(int k)
{
    long long result = 1;
    for (int i = 2; i <= k; ++i) result *= i;
    return result;
}

/*
* @brief вычисляет k - й член последовательности
* @param k - порядковый номер члена(>= 1)
* @return значение a_k
*/
double term(int k)
{
    long long f = factorial(k);
    double sign = (k % 2 ? -1.0 : 1.0);
    return sign / (double)(f * f);
}

/*
* @brief вычисляет сумму первых n членов последовательности
* @param n - количество членов(>= 1)
* @return S_n — сумму первых n членов
*/
double sumFirstN(int n)
{
    double s = 0.0;
    for (int k = 1; k <= n; ++k) s += term(k);
    return s;
}

/*
* @brief вычисляет сумму всех членов, модуль которых не меньше eps
* @param eps - положительный порог отсечения
* @return S_eps — искомую сумму
*/
double sumByEps(double eps)
{
    double s = 0.0;
    for (int k = 1; ; ++k)
    {
        double ak = term(k);
        if (std::abs(ak) < eps) break;
        s += ak;
    }
    return s;
}

/*
* @brief точка входа в программу
* @return 0 при корректном завершении, иначе 1
*/
int main()
{
    setlocale(LC_ALL, "Russian");

    int n;
    double eps;

    std::cout << "n (>=1): ";
    while (!(std::cin >> n) || n < 1)
    {
        std::cout << "Ошибка. Повторите ввод n: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::cout << "eps (>0): ";
    while (!(std::cin >> eps) || eps <= 0.0)
    {
        std::cout << "Ошибка. Повторите ввод eps: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    double sN = sumFirstN(n);
    double sEp = sumByEps(eps);

    std::cout.precision(10);
    std::cout << std::fixed;
    std::cout << "\nS_n = " << sN << '\n';
    std::cout << "S_eps = " << sEp << '\n';
    return 0;
}

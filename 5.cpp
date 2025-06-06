#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

/**
 * @brief Считывает целое число с клавиатуры с проверкой корректности ввода
 * @return Возвращает считанное целое число
 * @throw Завершает программу при ошибке ввода
 */
int getValue();

/**
 * @brief Считывает вещественное число с клавиатуры с проверкой корректности ввода
 * @return Возвращает считанное вещественное число
 * @throw Завершает программу при ошибке ввода
 */
double getDouble();

/**
 * @brief Проверяет корректность введенного количества членов ряда (n >= 1)
 * @param n Количество членов ряда для проверки
 * @throw Завершает программу при n < 1
 */
void checkN(const int n);

/**
 * @brief Вычисляет сумму первых n членов заданного ряда
 * @param n Количество суммируемых членов ряда
 * @return Сумма первых n членов ряда
 */
double sumN(const int n);

/**
 * @brief Вычисляет следующий член ряда по рекуррентной формуле
 * @param current Текущий член ряда (a_k)
 * @param i Индекс текущего члена (0-based, соответствует k-1)
 * @return Следующий член ряда (a_{k+1})
 */
double getNext(const double current, const int i);

/**
 * @brief Проверяет корректность введенной точности (e > 0)
 * @param e Точность вычислений для проверки
 * @throw Завершает программу при e <= 0
 */
void checkE(const double e);

/**
 * @brief Вычисляет сумму членов ряда с заданной точностью
 * @param e Требуемая точность вычислений
 * @return Сумма членов ряда, где абсолютное значение члена больше e
 */
double sumE(const double e);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(10);

    
    cout << "Введите число членов ряда для расчета: ";
    int n = getValue();
    checkN(n);
    cout << "Сумма " << n << " членов ряда равна " << sumN(n) << endl;

    
    cout << "Введите точность вычислений: ";
    double e = getDouble();
    checkE(e);
    cout << "Сумма ряда с точностью " << e << " равна " << sumE(e) << endl;

    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cerr << "Ошибка ввода: требуется целое число" << endl;
        abort();
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double getDouble()
{
    double value = 0.0;
    cin >> value;
    if (cin.fail())
    {
        cerr << "Ошибка ввода: требуется вещественное число" << endl;
        abort();
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

void checkN(const int n)
{
    if (n < 1)
    {
        cerr << "Ошибка: количество членов ряда должно быть ≥ 1" << endl;
        abort();
    }
}

double getNext(const double current, const int i)
{
    const int k_plus_1 = i + 2;  
    return current * (-1.0) / (k_plus_1 * k_plus_1);
}

double sumN(const int n)
{
    const double a1 = -1.0; 
    double sum = a1;
    double current = a1;

    for (int i = 1; i < n; ++i) {
        current = getNext(current, i - 1);  
        sum += current;
    }
    return sum;
}

void checkE(const double e)
{
    if (e <= 0.0)
    {
        cerr << "Ошибка: точность должна быть > 0" << endl;
        abort();
    }
}

double sumE(const double e)
{
    const double a1 = -1.0;
    const int max_iter = 1000;  
    double sum = a1;
    double current = a1;

    for (int i = 1; i <= max_iter; ++i) {
        if (fabs(current) <= e) {
            break;  
        }
        current = getNext(current, i - 1); 
        sum += current;
    }

    return sum;
}

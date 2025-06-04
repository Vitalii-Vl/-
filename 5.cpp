#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

/**
 * @brief считывает целое число с клавиатуры с проверкой ввода
 * @return считанное значение
*/
int getValue();

/**
 * @brief считывает вещественное число с клавиатуры с проверкой ввода
 * @return считанное значение
*/
double getDouble();

/**
 * @brief проверяет, что введенное значение удовлетваряет условию n>=1
 * @param n считанное значение
*/
void checkN(const int n);

/**
 * @brief Рассчитывает сумму n первых членов ряда
 * @param n заданное число членов
 * @return сумму n первых членов ряда
*/
double sumN(const int n);

/**
 * @brief Рассчитывает следующий член ряда через рекуррентное выражение
 * @param current текущий член ряда (a_{i+1})
 * @param i текущий 0-базовый индекс (соответствует k-1, если current это a_k)
 * @return следующий член ряда (a_{i+2})
*/
double getNext(const double current, const int i);

/**
 * @brief проверяет, что введенное значение удовлетваряет условию e>0
 * @param e считанное значение
*/
void checkE(const double e);

/**
 * @brief Рассчитывает сумму первых членов ряда, пока их модуль превышает e
 * @param e заданная точность
 * @return сумму первых членов ряда до заданного условия
*/
double sumE(const double e);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
*/
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(10); 

    cout << "Введите число членов ряда для расчета последовательности: ";
    int n = getValue();
    checkN(n);

    cout << "Сумма " << n << " членов ряда равна " << sumN(n) << endl;

    cout << "Введите погрешность для расчета последовательности: ";
    double e = getDouble();
    checkE(e);

    cout << "Сумма членов ряда с точностью е равна " << sumE(e) << endl;

    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода: Введите целое число." << endl;
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
        cout << "Ошибка ввода: Введите вещественное число." << endl;
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
        cout << "Ошибка ввода: Количество членов ряда N должно быть не менее 1." << endl;
        abort();
    }
}

double getNext(const double current, const int i)
{
    return current * (-1.0) / ((i + 2) * (i + 2)); 
}

double sumN(const int n)
{
    const double first_term = -1.0; 

    double current_term = first_term;
    double total_sum = 0.0;

    total_sum += current_term;

    
    for (int i = 0; i < n - 1; ++i) 
    {
        current_term = getNext(current_term, i); 
        total_sum += current_term;
    }
    return total_sum;
}

void checkE(const double e)
{
    if (!(e > 0))
    {
        cout << "Ошибка ввода: Погрешность E должна быть строго больше 0." << endl;
        abort();
    }
}

double sumE(const double e)
{
    const double first_term = -1.0; 

    double current_term = first_term;
    double total_sum = 0.0;
    int i = 0;

    while (fabs(current_term) > e) 
    {
        total_sum += current_term;
        current_term = getNext(current_term, i); 
        i++; 
    }
    return total_sum;
}

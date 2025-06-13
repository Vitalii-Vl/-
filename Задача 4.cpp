#include <iostream>
#include <limits>
#include <cmath>
#include <stdexcept>

using namespace std;

/**
 * @brief Считывает значение типа double с клавиатуры с проверкой на корректность ввода.
 * @return Введенное значение типа double.
 */
double getValue();

/**
 * @brief Проверяет, является ли шаг положительным.
 * @param step Шаг.
 */
void checkStep(const double step);

/**
 * @brief Вычисляет значение функции y(x) = sin(log(x)) - cos(log(x)) + 2*log(x).
 * @param x Аргумент функции.
 * @return Значение функции y(x).
 */
double getY(const double x);

/**
 * @brief Цикл вычисления y(x) от x_start до x_end с шагом delta с проверкой ln(x)
 * @param x_start – начальное значение
 * @param x_end – конечное значение
 * @param step – шаг изменения x
 */
void computeAndPrint(const double xstart, const double xend, const double step);

/**
 * @brief Главная функция программы.
 * @return 0, если программа выполнена корректно, иначе 1
 */
int main() 
{
    std::cout << "Enter xn: ";
    double xstart = getValue();

    std::cout << "Enter xk: ";
    double xend = getValue();

    std::cout << "Enter step: ";
    double step = getValue();

    checkStep(step);

    computeAndPrint(xstart, xend, step);
    return 0;
}


double getValue() {
    double value = 0;
    cin >> value;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        std::cout << "Incorrect value";
        abort();
    }
    return value;
}

void checkStep(const double step) {
    if (step <= 0) {
        std::cout << "Error value";
        abort();
    }
}

double getY(const double x){
    return sin(log(x)) - cos(log(x)) + 2 * log(x);
}

void computeAndPrint(const double x_start, const double x_end, const double delta)
{
    cout << "\nРезультаты:\n";
    for (double x = x_start; x <= x_end; x += delta) {
        if (x <= 0.0) {
            cout << "Пропущено x=" << x << ": вне области определения ln(x)\n";
            continue;
        }
        cout << "y(" << x << ") = " << getY(x) << endl;
    }
}

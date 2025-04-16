#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Функция для вычисления значения переменной 'a'.
 * 
 * @param x Значение переменной x.
 * @param y Значение переменной y.
 * @param z Значение переменной z.
 * @return Вычисленное значение 'a'.
 */
double calculate_a(double x, double y, double z) {
    return exp(-y * z) * sin(x * z - y) - sqrt(abs(y * z + x));
}

/**
 * @brief Функция для вычисления значения переменной 'b'.
 * 
 * @param y Значение переменной y.
 * @param z Значение переменной z.
 * @param a Значение переменной a.
 * @return Вычисленное значение 'b'.
 */
double calculate_b(double y, double z, double a) {
    return y * sin(a * z * z * cos(2 * z)) - 1;
}

int main() {
    // Исходные данные (константы)
    const double x = -0.5;
    const double y = 1.7;
    const double z = 0.44;

    // Вывод исходных данных
    cout << "Исходные данные:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;

    // Вычисление значений a и b
    double a = calculate_a(x, y, z);
    double b = calculate_b(y, z, a);

    // Вывод результатов
    cout << "\nРезультаты вычислений:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    return 0;
}

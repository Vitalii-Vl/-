#include <iostream>
#include <limits>
#include <cmath>
#include <stdexcept>

using namespace std;

/**
 * @brief Считывает значение типа double с клавиатуры с проверкой на корректность ввода.
 * @return Введенное значение типа double.
 * @throws std::runtime_error Если ввод некорректен.
 */
double getValue();

/**
 * @brief Проверяет, является ли шаг положительным.
 * @param step Шаг.
 * @throws std::runtime_error Если шаг не является положительным.
 */
void checkStep(const double step);

/**
 * @brief Вычисляет значение функции y(x) = sin(log(x)) - cos(log(x)) + 2*log(x).
 * @param x Аргумент функции.
 * @return Значение функции y(x).
 * @throws std::domain_error Если x не входит в область определения функции (x <= 0).
 */
double getY(const double x);

/**
 * @brief Главная функция программы.
 * @return 0, если программа выполнена корректно, иначе 1
 */
int main() {
    double xstart, xend, step;

  
        cout <<"Enter xn: "
        xstart = getValue();

        cout <<"Enter xk: ";
        xend = getValue();

        cout <<"Enter step: ";
        step = getValue();

        checkStep(step);

        for (double x = xstart; x <= xend; x += step) { 
                cout <<"x = " <<x <<" y = " <<getY(x) <<endl;

    return 0;
}

double getValue() {
    double value = 0;
    cin >> value;

    if (cin.fail()) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Incorrect value entered.  Please enter a number.");
    }

    return value;
}

void checkStep(const double step) {
    if (step <= 0) {
        throw runtime_error("Шаг должен быть положительным.");
    }
}

double getY(const double x) {
    if (x <= 0) {
        throw domain_error("X должен быть больше 0.");
    }
    return sin(log(x)) - cos(log(x)) + 2 * log(x);
}

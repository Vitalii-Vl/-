#include <iostream>
#include <cmath>
#include <iomanip> // для setprecision

using namespace std;

int main() {
  // Исходные данные
  double x = -0.5;
  double y = 1.7;
  double z = 0.44;

  // Вывод исходных данных
  cout << "Исходные данные:" << endl;
  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
  cout << "z = " << z << endl;


  // Вычисление a
  double a = exp(-y * z) * sin(x * z - y) - sqrt(y * z + x);

  // Вычисление b
  double b = y * sin(a * z * z * cos(2 * z)) - 1;


  // Вывод результатов (с заданной точностью)
  cout << "\nРезультаты вычислений:" << endl;
  cout << fixed << setprecision(10); // Устанавливаем точность вывода до 10 знаков после запятой
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;

  return 0;
}

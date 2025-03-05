#include <iostream>
#include <cmath>
#include <iomanip> // для setprecision

using namespace std;

double getA(const double x, const double y, const double z);


int main() {
  // Исходные данные
  double x = -0.5;
  double y = 1.7;
  double z = 0.44;

  // Вычисление b
  double b = y * sin(a * z * z * cos(2 * z)) - 1;


  // Вывод результатов (с заданной точностью)
  cout << "\nРезультаты вычислений:" << endl;
  cout << fixed << setprecision(10); // Устанавливаем точность вывода до 10 знаков после запятой
  cout << "a = " << getA(x, y, z) << endl;
  cout << "b = " << b << endl;

  return 0;
}

double getA(const double x, const double y, const double z)
{
    return exp(-y * z) * sin(x * z - y) - sqrt(y * z + x);
}

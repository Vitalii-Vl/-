#include <iostream>
#include <math.h>

// Вариант 4
// а = ⅇ ^ (-yz)⋅sin⁡〖(xz - y)〗 - √(| yz + x | )
// b = y sin⁡(az ^ 2 cos⁡2z) - 1

// float - тип данных, который хранят дробные числа
// double - тип данных, который хранят дробные числа

using namespace std;

int main()
{
  // Смена кодировки для вывода русского языка
  setlocale(LC_ALL, "Russian");

  float a, b; // переменные, содержащие значения функций
  const float z = 0.44; // константа по условию задачи
  const float x = -0.5; // константа по условию задачи
  const float y = 1.7; // константа по условию задачи

  a = exp(-y * z) * sin(x * z - y) - sqrt(abs(y * z + x));
  b = y * sin(y * pow(z, 2) * cos(2 * z)) - 1;

  cout << "Функция a: " << a << endl;
  cout << "Функция b: " << b << endl;

}

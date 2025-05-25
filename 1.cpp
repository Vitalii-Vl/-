#include <iostream>
#include <cstdlib>
#include <ctime>

/*
* @brief возвращает модуль целого числа без использования <cmath>
* @param x - исходное число
* @return |x|
*/
int absInt(int x) { return x < 0 ? -x : x; }

/*
* @brief заполняет массив значениями(случайно либо вручную)
* @param a - указатель на начало массива
* @param n - размер массива
* @param randomFill - true: случайные числа; false: ввод с клавиатуры
* @param left - нижняя граница диапазона случайных чисел
* @param right - верхняя граница диапазона случайных чисел
*/
void fillArray(int* a, int n, bool randomFill, int left, int right)
{
    if (randomFill) std::srand(std::time(0));

    for (int i = 0; i < n; ++i)
    {
        if (randomFill)
            a[i] = std::rand() % (right - left + 1) + left;
        else
        {
            std::cout << "a[" << i << "] = ";
            std::cin >> a[i];
        }
    }
}

/*
* @brief вычисляет сумму чётных элементов массива
* @param a - указатель на массив(const)
* @param n - размер массива
* @return сумму чётных элементов
*/
int sumEven(const int* a, int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        if (a[i] % 2 == 0) sum += a[i]; // sum = sum + a[i]
    return sum;
}

/*
* @brief подсчитывает количество двухзначных элементов массива
* @param a - указатель на массив(const)
* @param n - размер массива
* @return количество элементов с модулем 10…99
*/
int countTwoDigit(const int* a, int n)
{
    int k = 0;
    for (int i = 0; i < n; ++i)
    {
        int v = absInt(a[i]);
        if (v >= 10 && v <= 99) ++k;
    }
    return k;
}

/*
* @brief заменяет последнее отрицательное значение массива на |a[0]|
* @param a - указатель на массив
* @param n - размер массива
*/
void replaceLastNeg(int* a, int n)
{
    for (int i = n - 1; i >= 0; --i)
        if (a[i] < 0) { a[i] = absInt(a[0]); break; }
}

/*
* @brief точка входа в программу 
* @return 0 при корректном завершении, иначе 1
*/
int main()
{
    int n;
    std::cout << "Размер массива n: ";
    std::cin >> n;

    int* a = new int[n];

    char mode;
    std::cout << "Случайные данные (r) или вручную (m)? ";
    std::cin >> mode;
    fillArray(a, n, (mode == 'r' || mode == 'R'), -1000, 1000);

    std::cout << "\nИсходный массив:\n";
    for (int i = 0; i < n; ++i) std::cout << a[i] << ' ';
    std::cout << "\n\n";

    std::cout << "Сумма чётных элементов: " << sumEven(a, n) << '\n';
    std::cout << "Количество двухзначных элементов: " << countTwoDigit(a, n) << '\n';

    replaceLastNeg(a, n);

    std::cout << "Массив после замены последнего отрицательного:\n";
    for (int i = 0; i < n; ++i) std::cout << a[i] << ' ';
    std::cout << '\n';

    delete[] a;
    return 0;
}

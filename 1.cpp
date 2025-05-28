#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

/**
 * @brief Ввод положительного размера массива
 * @param prompt – текст запроса
 * @return положительное целое (size_t)
 */
size_t inputSize(const string& prompt);

/**
 * @brief Ввод режима заполнения массива ('R' – случайно, 'M' – вручную)
 * @param prompt – текст запроса
 * @return 'R' или 'M'
 */
char inputMode(const string& prompt);

/**
 * @brief Ввод целого числа с проверкой корректности
 * @param prompt – текст запроса
 * @return введённое целое число
 */
int inputInt(const string& prompt);

/**
 * @brief Заполняет массив согласно выбранному режиму
 * @param a – указатель на начало массива
 * @param n – размер массива
 * @param mode – 'R' или 'M'
 * @param left – нижняя граница рандома
 * @param right – верхняя граница рандома
 */
void fillArray(int* a, size_t n, const char& mode, const int& left, const int& right);

/**
 * @brief Вывод массива на экран
 */
void printArray(const int* a, size_t n);

/**
 * @brief Считает сумму чётных элементов массива
 * @param a – указатель на массив
 * @param n – его размер
 * @return сумма чётных значений
 */
int sumEven(const int* a, size_t n);

/**
 * @brief Считает количество двухзначных по модулю элементов
 * @param a – указатель на массив
 * @param n – его размер
 * @return количество элементов с abs(a[i]) от 10 до 99
 */
size_t countTwoDigit(const int* a, size_t n);

/**
 * @brief Заменяет последнее отрицательное значение на abs(a[0])
 * @param a – указатель на массив
 * @param n – его размер
 */
void replaceLastNeg(int* a, size_t n);


int main()
{
    setlocale(LC_ALL, "Russian");

    size_t n = inputSize("Введите размер массива n (>0): ");
    int* a = new int[n];

    char mode = inputMode("Режим заполнения (R – случайно, M – вручную): ");
    fillArray(a, n, mode, -1000, 1000);

    cout << "\nИсходный массив:\n";
    printArray(a, n);
    cout << "\n";

    cout << "Сумма чётных: " << sumEven(a, n) << '\n';
    cout << "Двухзначных по модулю: " << countTwoDigit(a, n) << '\n';

    replaceLastNeg(a, n);

    cout << "\nПосле замены последнего отрицательного:\n";
    printArray(a, n);

    delete[] a;
    return 0;
}

size_t inputSize(const string& prompt)
{
    long long tmp;
    while (true) {
        cout << prompt;
        cin >> tmp;
        if (cin.fail() || tmp <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка: введите положительное целое.\n";
        }
        else {
            return static_cast<size_t>(tmp);
        }
    }
}

char inputMode(const string& prompt)
{
    char m;
    while (true) {
        cout << prompt;
        cin >> m;
        cin.ignore(10000, '\n');
        switch (m) 
        {
            case 'r': case 'R': return 'R';
            case 'm': case 'M': return 'M';
            
            default:
                cout << "Ошибка: введите 'R' или 'M'.\n";
        }
    }
}

int inputInt(const string& prompt)
{
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка: введите целое число.\n";
        }
        else {
            return value;
        }
    }
}

void printArray(const int* a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
}

void fillArray(int* a, size_t n, const char& mode, const int& left, const int& right)
{
    if (mode == 'R')
        srand(time(0));

    for (size_t i = 0; i < n; ++i) {
        if (mode == 'R') {
            a[i] = rand() % (right - left + 1) + left;
        }
        else {
            a[i] = inputInt("a[" + to_string(i) + "] = ");
        }
    }
}

int sumEven(const int* a, size_t n)
{
    int sum = 0;
    for (size_t i = 0; i < n; ++i)
        if (a[i] % 2 == 0)
            sum += a[i];
    return sum;
}
size_t countTwoDigit(const int* a, size_t n)
{
    size_t cnt = 0;
    for (size_t i = 0; i < n; ++i) {
        int v = abs(a[i]);
        if (v >= 10 && v <= 99)
            ++cnt;
    }
    return cnt;
}

void replaceLastNeg(int* a, size_t n)
{
    for (size_t i = n; i-- > 0; ) {
        if (a[i] < 0) {
            a[i] = abs(a[0]);
            break;
        }
    }
}

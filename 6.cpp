#include <iostream>
#include <string>

using namespace std;

enum class FillMode
{
    RANDOM = 1,
    MANUAL = 2
};

/**
 * @brief Ввод положительного размера массива
 * @param prompt – строка-ввода
 * @return размер массива (>0)
 */
size_t inputSize(const string& prompt);

/**
 * @brief Ввод режима заполнения массива
 * @param prompt – строка-ввода
 * @return FillMode::RANDOM или FillMode::MANUAL
 */
FillMode inputMode(const string& prompt);

/**
 * @brief Ввод целого числа
 * @param prompt – строка-ввода
 * @return введённое целое число
 */
int inputInt(const string& prompt);

/**
 * @brief Заполнение массива случайными числами или вручную
 * @param a – указатель на начало массива
 * @param n – размер массива
 * @param mode – режим заполнения (RANDOM/MANUAL)
 */
void fillArray(int* const a, size_t n, FillMode mode, int left, int right);

/**
 * @brief Вывод массива на экран
 * @param a – указатель на начало массива
 * @param n – размер массива
 */
void printArray(const int* a, size_t n);

/**
 * @brief Вычисление суммы чётных элементов массива
 * @param a – указатель на начало массива
 * @param n – размер массива
 * @return сумма чётных элементов
 */
int sumEven(const int* a, size_t n);

/**
 * @brief Подсчёт количества элементов с двухзначным модулем
 * @param a – указатель на начало массива
 * @param n – размер массива
 * @return количество элементов, |a[i]| от 10 до 99
 */
size_t countTwoDigit(const int* a, size_t n);

/**
 * @brief Замена последнего отрицательного элемента на |a[0]|
 * @param a – указатель на начало массива
 * @param n – размер массива
 */
void replaceLastNeg(int* a, size_t n);

int main()
{
    setlocale(LC_ALL, "Russian");
    const size_t n = inputSize("Размер массива n (>0): ");

    cout << "\nВведите границы диапазона случайных чисел\n";
    const int left = inputInt(" Левая граница: ");
    const int right = inputInt(" Правая граница: ");

    if (left > right)
    {
        cout << "Ошибка: левая граница больше правой!\n";
        abort();
    }

    FillMode mode = inputMode("Заполнение (R — случайно, M — вручную): ");

    int* a = new int[n]();
    fillArray(a, n, mode, left, right);
    cout << "\nИсходный массив:\n";
    printArray(a, n);

    cout << "\nСумма чётных: " << sumEven(a, n) << "\nДвухзначных: " << countTwoDigit(a, n) << '\n';

    int* b = new int[n];
    std::copy(a, a + n, b);

    replaceLastNeg(b, n);
    cout << "\nПосле замены последнего отрицательного:\n";
    printArray(b, n);

    delete[] a;
    delete[] b;
    return 0;
}

size_t inputSize(const string& prompt)
{
    int tmp = 0;
    cout << prompt;
    cin >> tmp;
    if (cin.fail() || tmp <= 0)
    {
        cout << "Ошибка: некорректный размер!\n";
        abort();
    }
    return static_cast<size_t>(tmp);
}

FillMode inputMode(const string& prompt)
{
    char c = 0;
    cout << prompt;
    cin >> c;
    if (c != 'R' && c != 'r' && c != 'M' && c != 'm')
    {
        cout << "Ошибка: режим должен быть R/r или M/m!\n";
        abort();
    }
    return (c == 'R' || c == 'r') ? FillMode::RANDOM : FillMode::MANUAL;
}

int inputInt(const string& prompt)
{
    int v = 0;
    cout << prompt;
    cin >> v;
    if (cin.fail())
    {
        cout << "Ошибка ввода целого числа!\n";
        abort();
    }
    return v;
}

void fillArray(int* const a, size_t n, FillMode mode, int left, int right)
{
    if (mode == FillMode::RANDOM)
        srand(static_cast<unsigned>(time(nullptr)));

    for (size_t i = 0; i < n; ++i)
    {
        if (mode == FillMode::RANDOM)
        {
            a[i] = rand() % (right - left + 1) + left;
        }
        else
        {
            a[i] = inputInt("a[" + to_string(i) + "] = ");
        }
    }
}

void printArray(const int* a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << '\n';
}

int sumEven(const int* a, size_t n)
{
    int s = 0;
    for (size_t i = 0; i < n; ++i)
        if (a[i] % 2 == 0)
            s += a[i];
    return s;
}


size_t countTwoDigit(const int* a, size_t n)
{
    size_t count = 0;
    for (size_t i = 0; i < n; ++i)
    {
        int v = abs(a[i]);
        if (v >= 10 && v <= 99)
            ++count;
    }
    return count;
}

void replaceLastNeg(int* a, size_t n)
{
    for (size_t i = n; i-- > 0; )
        if (a[i] < 0)
        {
            a[i] = abs(a[0]);
            break;
        }
}

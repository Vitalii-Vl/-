#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

enum FillMode 
{ 
    RANDOM = 1, 
    MANUAL = 2 
};

/**
 * @brief Ввод положительного размера (число строк или столбцов)
 * @param prompt – текст запроса
 * @return положительное целое (size_t)
 */
size_t inputSize(const string& prompt);

/**
 * @brief Ввод режима заполнения массива
 * @param prompt – текст запроса
 * @return FillMode::RANDOM или FillMode::MANUAL
 */
FillMode inputMode(const string& prompt);

/**
 * @brief Ввод целого числа с проверкой корректности
 * @param prompt – текст запроса
 * @return введённое целое
 */
int inputInt(const string& prompt);

/**
 * @brief Заполняет матрицу n×m случайно или вручную
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 * @param mode – режим заполнения
 * @param left – нижняя граница случайных чисел
 * @param right – верхняя граница случайных чисел
 */
void fillMatrix(int** const& matrix, size_t n, size_t m, FillMode mode, int left, int right);

/**
 * @brief Выводит матрицу на экран
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 */
void printMatrix(int* const* const& matrix, size_t n, size_t m);

/**
 * @brief В каждом столбце заменяет элемент с минимальным по модулю значением на противоположный
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 */
void replaceMinAbsPerCol(int** const& matrix, size_t n, size_t m);

/**
 * @brief Удаляет все строки, содержащие глобальный максимум
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 */
void removeRowsWithMax(int**& matrix, size_t& n, size_t m);

/**
 * @brief Точка входа в программу
 * @return 0 при успешном завершении
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    size_t n = inputSize("Введите число строк n (>0): ");
    size_t m = inputSize("Введите число столбцов m (>0): ");

    int** matrix = new int* [n];
    for (size_t i = 0; i < n; ++i)
        matrix[i] = new int[m];

    FillMode mode = inputMode("Выберите режим заполнения: R — случайно, M — вручную: ");

    const int LEFT_BOUND = -1000;
    const int RIGHT_BOUND = 1000;
    fillMatrix(matrix, n, m, mode, LEFT_BOUND, RIGHT_BOUND);

    cout << "\nИсходная матрица:\n";
    printMatrix(matrix, n, m);

    replaceMinAbsPerCol(matrix, n, m);
    cout << "\nПосле замены элементов с минимальным модулем:\n";
    printMatrix(matrix, n, m);

    removeRowsWithMax(matrix, n, m);
    cout << "\nПосле удаления строк с глобальным максимумом:\n";
    printMatrix(matrix, n, m);

    for (size_t i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}

size_t inputSize(const string& prompt)
{
    long long tmp;
    cout << prompt;
    while (!(cin >> tmp) || tmp <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка: введите положительное целое.\n" << prompt;
    }
    return static_cast<size_t>(tmp);
}

FillMode inputMode(const string& prompt)
{
    char c;
    cout << prompt;
    cin >> c;
    cin.ignore(10000, '\n');
    while (c != 'R' && c != 'r' && c != 'M' && c != 'm') {
        cout << "Ошибка: введите 'R' или 'M': ";
        cin >> c;
        cin.ignore(10000, '\n');
    }
    return (c == 'R' || c == 'r') ? RANDOM : MANUAL;
}

int inputInt(const string& prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка: введите целое число.\n" << prompt;
    }
    return value;
}

void fillMatrix(int** const& matrix, size_t n, size_t m, FillMode mode, int left, int right)
{
    if (mode == RANDOM)
        srand(static_cast<unsigned>(time(nullptr)));

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            matrix[i][j] = (mode == RANDOM) ? rand() % (right - left + 1) + left : inputInt("matrix[" + to_string(i) + "][" + to_string(j) + "] = ");
}
void printMatrix(int* const* const& matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            cout << matrix[i][j] << '\t';
        cout << '\n';
    }
}

void replaceMinAbsPerCol(int** const& matrix, size_t n, size_t m)
{
    for (size_t j = 0; j < m; ++j) {
        size_t minRow = 0;
        int minAbs = abs(matrix[0][j]);
        for (size_t i = 1; i < n; ++i) {
            int v = abs(matrix[i][j]);
            if (v < minAbs) {
                minAbs = v;
                minRow = i;
            }
        }
        matrix[minRow][j] = -matrix[minRow][j];
    }
}

void removeRowsWithMax(int**& matrix, size_t& n, size_t m)
{
    int globalMax = matrix[0][0];
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] > globalMax)
                globalMax = matrix[i][j];

    size_t keep = 0;
    for (size_t i = 0; i < n; ++i) {
        bool hasMax = false;
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] == globalMax) { hasMax = true; break; }
        if (!hasMax) ++keep;
    }

    int** newMat = new int* [keep];
    size_t idx = 0;
    for (size_t i = 0; i < n; ++i) {
        bool hasMax = false;
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] == globalMax) { hasMax = true; break; }
        if (hasMax) {
            delete[] matrix[i];
        }
        else {
            newMat[idx++] = matrix[i];
        }
    }

    delete[] matrix;
    matrix = newMat;
    n = keep;
}

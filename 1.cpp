#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

/**
 * @brief Ввод положительного размера (число строк или столбцов)
 * @param prompt – текст запроса
 * @return положительное целое (size_t)
 */
size_t inputSize(const string& prompt);

/**
 * @brief Ввод режима заполнения ('R' – случайно, 'M' – вручную)
 * @param prompt – текст запроса
 * @return 'R' или 'M'
 */
char inputMode(const string& prompt);

/**
 * @brief Ввод целого числа с проверкой корректности
 * @param prompt – текст запроса
 * @return введённое целое
 */
int inputInt(const string& prompt);

/**
 * @brief Заполняет матрицу n×m случайно или вручную
 * @param matrix – указатель на массив указателей (n строк)
 * @param n – число строк
 * @param m – число столбцов
 * @param mode – 'R' или 'M'
 * @param left – нижняя граница рандома
 * @param right – верхняя граница рандома
 */
void fillMatrix(int** matrix, size_t n, size_t m, const char& mode, const int& left, const int& right);

/**
 * @brief Выводит матрицу на экран
 * @param matrix – указатель на массив указателей
 * @param n – число строк
 * @param m – число столбцов
 * @return void
 */
void printMatrix(int** matrix, size_t n, size_t m);

/**
 * @brief В каждом столбце заменяет элемент с минимальным по модулю значением на противоположный
 * @param matrix – указатель на массив указателей
 * @param n – число строк
 * @param m – число столбцов
 */
void replaceMinAbsPerCol(int** matrix, size_t n, size_t m);

/**
 * @brief Удаляет все строки, содержащие глобальный максимум
 * @param matrix – ссылка на указатель на массив указателей (изменяется)
 * @param n – ссылка на число строк (изменяется)
 * @param m – число столбцов
 */
void removeRowsWithMax(int**& matrix, size_t& n, size_t m);

int main()
{
    setlocale(LC_ALL, "Russian");
    size_t n = inputSize("Введите число строк n (>0): ");
    size_t m = inputSize("Введите число столбцов m (>0): ");
    int** matrix = new int* [n];
    for (size_t i = 0; i < n; ++i)
        matrix[i] = new int[m];
    char mode = inputMode("Режим заполнения (R – случайно, M – вручную): ");
    fillMatrix(matrix, n, m, mode, -1000, 1000);
    cout << "\nИсходная матрица:\n";
    printMatrix(matrix, n, m);
    replaceMinAbsPerCol(matrix, n, m);
    cout << "\nПосле замены минимальных по модулю в каждом столбце:\n";
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
    while (true) {
        cout << prompt;
        if (!(cin >> tmp) || tmp <= 0) {
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
        switch (m) {
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
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка: введите целое число.\n";
        }
        else {
            return value;
        }
    }
}

void fillMatrix(int** matrix, size_t n, size_t m, const char& mode, const int& left, const int& right)
{
    if (mode == 'R')
        srand(static_cast<unsigned>(time(nullptr)));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            matrix[i][j] = (mode == 'R')
            ? rand() % (right - left + 1) + left
            : inputInt("matrix[" + to_string(i) + "][" + to_string(j) + "] = ");
}


void printMatrix(int** matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            cout << matrix[i][j] << '\t';
        cout << '\n';
    }
}

void replaceMinAbsPerCol(int** matrix, size_t n, size_t m)
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
    size_t keepCount = 0;
    for (size_t i = 0; i < n; ++i) {
        bool hasMax = false;
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] == globalMax) {
                hasMax = true;
                break;
            }
        if (!hasMax)
            ++keepCount;
    }
    int** newMatrix = new int* [keepCount];
    size_t idx = 0;
    for (size_t i = 0; i < n; ++i) {
        bool hasMax = false;
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] == globalMax) {
                hasMax = true;
                break;
            }
        if (hasMax) {
            delete[] matrix[i];
        }
        else {
            newMatrix[idx++] = matrix[i];
        }
    }
    delete[] matrix;
    matrix = newMatrix;
    n = keepCount;
}

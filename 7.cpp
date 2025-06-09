#include <iostream>
#include <string>

using namespace std;

enum FillMode
{
    RANDOM = 1,
    MANUAL = 2
};

/**
 * @brief Ввод положительного размера
 * @param prompt – текст запроса
 * @return положительное целое
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
 * @brief Вводит границы диапазона генерации случайных чисел
 * @param left – левая граница
 * @param right – правая граница
 */
void inputBounds(int& left, int& right);

/**
 * @brief Заполняет матрицу n×m случайно или вручную
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 * @param mode – режим заполнения
 * @param left – левая граница диапазона
 * @param right – правая граница диапазона
 */
void fillMatrix(int** const& matrix, const size_t n, const size_t m, const FillMode mode, const int left, const int right);

/**
 * @brief Выводит матрицу на экран
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 */
void printMatrix(int* const* const& matrix, const size_t n, const size_t m);

/**
 * @brief В каждом столбце заменяет элемент с минимальным по модулю значением на противоположный
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 */
void replaceMinAbsPerCol(int** const& matrix, const size_t n, const size_t m);

/**
 * @brief Удаляет все строки, содержащие глобальный максимум
 * @param matrix – ссылка на указатель на строки
 * @param n – число строк
 * @param m – число столбцов
 */
void removeRowsWithMax(int** matrix, size_t& n, const size_t m);

/**
 * @brief Выделяет динамическую матрицу n×m
 * @param n – число строк
 * @param m – число столбцов
 * @return указатель на массив строк
 */
int** allocateMatrix(const size_t n, const size_t m);

/**
 * @brief Освобождает память матрицы n×m
 * @param matrix – указатель на массив строк
 * @param n – число строк
 */
void deallocateMatrix(int** matrix, const size_t n);

/**
 * @brief Точка входа в программу
 * @return код завершения (0 – успех)
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    const size_t n = inputSize("Введите число строк n (>0): ");
    const size_t m = inputSize("Введите число столбцов m (>0): ");
    int left, right;
    inputBounds(left, right);
    const FillMode mode = inputMode("Выберите режим заполнения: R — случайно, M — вручную: ");

    int** matrix = allocateMatrix(n, m);
    fillMatrix(matrix, n, m, mode, left, right);

    cout << "\nИсходная матрица:\n";
    printMatrix(matrix, n, m);

    replaceMinAbsPerCol(matrix, n, m);

    removeRowsWithMax(matrix, n, m);

    deallocateMatrix(matrix, n);

    return 0;
}

size_t inputSize(const string& prompt)
{
    int tmp = 0;
    cout << prompt;
    cin >> tmp;
    if (cin.fail() || tmp <= 0)
    {
        cout << "Ошибка!.\n";
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
        cout << "Ошибка!.\n";
        abort();
    }
    return (c == 'R' || c == 'r') ? RANDOM : MANUAL;
}

int inputInt(const string& prompt)
{
    int v = 0;
    cout << prompt;
    cin >> v;
    if (cin.fail())
    {
        cout << "Ошибка!.\n";
        abort();
    }
    return v;
}

void inputBounds(int& left, int& right)
{
    left = inputInt(" Левая граница: ");
    right = inputInt(" Правая граница: ");
    if (left > right)
    {
        cout << "Ошибка!.\n";
        abort();
    }
}

int** allocateMatrix(const size_t n, const size_t m)
{
    int** mat = new int*[n];
    for (size_t i = 0; i < n; ++i)
        mat[i] = new int[m];
    return mat;
}


void deallocateMatrix(int** matrix, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

void fillMatrix(int** const& matrix, const size_t n, const size_t m, const FillMode mode, const int left, const int right)
{
    if (mode == RANDOM)
        srand(static_cast<unsigned>(time(nullptr)));

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            matrix[i][j] = (mode == RANDOM) ? rand() % (right - left + 1) + left : inputInt("matrix[" + to_string(i) + "][" + to_string(j) + "] = ");
}

void printMatrix(int* const* const& matrix, const size_t n, const size_t m)
{
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j)
            cout << matrix[i][j] << '\t';
        cout << '\n';
    }
}

void replaceMinAbsPerCol(int** const& matrix, const size_t n, const size_t m)
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
    cout << "\nПосле замены элементов с минимальным модулем:\n";
    printMatrix(matrix, n, m);
}

void removeRowsWithMax(int** matrix, size_t& n, const size_t m)
{
    int globalMax = matrix[0][0];
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] > globalMax)
                globalMax = matrix[i][j];

    size_t write = 0;
    for (size_t i = 0; i < n; ++i) {
        bool hasMax = false;
        for (size_t j = 0; j < m; ++j)
            if (matrix[i][j] == globalMax) { hasMax = true; break; }
        if (!hasMax)
            matrix[write++] = matrix[i];
        else
            delete[] matrix[i];
    }
    n = write;
    cout << "\nПосле удаления строк с глобальным максимумом:\n";
    printMatrix(matrix, n, m);
}

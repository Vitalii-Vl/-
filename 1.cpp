#include <iostream>
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 
#include <limits>
#include <cmath> 
#include <vector>

/**
 * @brief Создает динамический двумерный массив заданных размеров.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Указатель на указатель (int**), представляющий созданный массив.
 */
int** createArray(const size_t rows, const size_t cols);

/**
 * @brief Освобождает память, выделенную для двумерного массива.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк в массиве.
 */
void deleteArray(int** arr, const size_t rows);

/**
 * @brief Заполняет массив случайными целыми числами в заданном диапазоне.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @param min Минимальное значение.
 * @param max Максимальное значение.
 */
void fillArrayRandom(int** arr, const size_t rows, const size_t cols, const int min, const int max);

/**
 * @brief Заполняет массив целыми числами, вводимыми с клавиатуры.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void fillArrayKeyboard(int** arr, const size_t rows, const size_t cols);

/**
 * @brief Предлагает пользователю выбрать способ заполнения массива (случайно или с клавиатуры).
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @param min Минимальное значение для случайного заполнения.
 * @param max Максимальное значение для случайного заполнения.
 */
void chooseFillMethod(int** arr, const size_t rows, const size_t cols, const int min, const int max);

/**
 * @brief Выводит содержимое двумерного массива на консоль.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void printArray(int** arr, const size_t rows, const size_t cols);

/**
 * @brief Находит минимальный по модулю элемент в заданном столбце и заменяет его на противоположный.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param colIndex Индекс столбца, который нужно обработать.
 */
void processColumnMinAbs(int** arr, const size_t rows, const size_t colIndex);

/**
 * @brief Проходит по каждому столбцу массива и заменяет минимальный по модулю элемент в нем на противоположный.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void replaceMinAbsInEachColumn(int** arr, const size_t rows, const size_t cols);

/**
 * @brief Находит максимальный элемент во всем массиве.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Максимальное значение в массиве.
 */
int findOverallMax(int** arr, const size_t rows, const size_t cols);

/**
 * @brief Проверяет, содержит ли заданная строка массива определенное значение.
 * @param row Указатель на массив (строку).
 * @param cols Количество столбцов в строке.
 * @param value Значение для поиска.
 * @return true, если строка содержит значение, false в противном случае.
 */
bool rowContainsValue(const int* row, const size_t cols, const int value);

/**
 * @brief Создает копию массива с удаленными строками, содержащими максимальный элемент.
 * @param arr Исходный массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @param newRows Ссылка на переменную для хранения нового количества строк.
 * @return Указатель на новый массив.
 */
int** deleteRowsContainingMax(int** arr, const size_t rows, const size_t cols, size_t& newRows);

/**
 * @brief Ввод целого числа с проверкой.
 * @param prompt Приглашение для ввода.
 * @return Введенное целое число.
 */
int inputInt(const std::string& prompt);

/**
 * @brief Ввод целого числа в заданном диапазоне с проверкой.
 * @param prompt Приглашение для ввода.
 * @param min Минимальное допустимое значение.
 * @param max Максимальное допустимое значение.
 * @return Введенное целое число.
 */
int inputIntInRange(const std::string& prompt, const int min, const int max);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    const size_t n = static_cast<size_t>(inputIntInRange("Введите количество строк N: ", 1, std::numeric_limits<int>::max()));
    const size_t m = static_cast<size_t>(inputIntInRange("Введите количество столбцов M: ", 1, std::numeric_limits<int>::max()));

    int** matrix = createArray(n, m);

    const int minVal = inputInt("Введите минимальное значение для случайного заполнения: ");
    const int maxVal = inputIntInRange("Введите максимальное значение для случайного заполнения: ", minVal, std::numeric_limits<int>::max());

    chooseFillMethod(matrix, n, m, minVal, maxVal);

    std::cout << "\n--- Исходный массив ---" << std::endl;
    printArray(matrix, n, m);

    int** task1Matrix = createArray(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            task1Matrix[i][j] = matrix[i][j];
        }
    }

    std::cout << "\n--- Выполнение Задачи 1: Замена мин. по модулю в каждом столбце ---" << std::endl;
    replaceMinAbsInEachColumn(task1Matrix, n, m);
    std::cout << "Массив после Задачи 1:" << std::endl;
    printArray(task1Matrix, n, m);
    deleteArray(task1Matrix, n);

    int** task2Matrix = createArray(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            task2Matrix[i][j] = matrix[i][j];
        }
    }

    std::cout << "\n--- Выполнение Задачи 2: Удаление строк, содержащих максимальные элементы ---" << std::endl;
    size_t newRows = 0;
    int** resultMatrix = deleteRowsContainingMax(task2Matrix, n, m, newRows);
    deleteArray(task2Matrix, n);

    std::cout << "Массив после Задачи 2:" << std::endl;
    if (newRows > 0) {
        printArray(resultMatrix, newRows, m);
        deleteArray(resultMatrix, newRows);
    } else {
        std::cout << "Все строки были удалены." << std::endl;
    }

    deleteArray(matrix, n);

    return 0;
}

int** createArray(const size_t rows, const size_t cols) {
    int** arr = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
    }
    return arr;
}

void deleteArray(int** arr, const size_t rows) {
    if (arr == nullptr) {
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

void fillArrayRandom(int** arr, const size_t rows, const size_t cols, const int min, const int max) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            arr[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void fillArrayKeyboard(int** arr, const size_t rows, const size_t cols) {
    std::cout << "Пожалуйста, введите элементы массива:" << std::endl;
    for (size_t i = 0; i < rows; ++i) {
        std::cout << "Строка " << i + 1 << ":" << std::endl;
        for (size_t j = 0; j < cols; ++j) {
            arr[i][j] = inputInt("Элемент [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
        }
    }
}

void chooseFillMethod(int** arr, const size_t rows, const size_t cols, const int min, const int max) {
    char choice;
    std::cout << "Как заполнить массив? (R - случайными числами, K - с клавиатуры): ";
    std::cin >> choice;
    choice = toupper(choice);
    
    if (choice == 'R') {
        fillArrayRandom(arr, rows, cols, min, max);
    } else {
        fillArrayKeyboard(arr, rows, cols);
    }
}

void printArray(int** arr, const size_t rows, const size_t cols) {
    if (arr == nullptr || rows == 0 || cols == 0) {
        std::cout << "Массив пуст или некорректных размеров." << std::endl;
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << std::setw(5) << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void processColumnMinAbs(int** arr, const size_t rows, const size_t colIndex) {
    if (rows == 0) return;

    int minAbsVal = std::abs(arr[0][colIndex]);
    size_t minAbsRowIndex = 0;

    for (size_t i = 1; i < rows; ++i) {
        if (std::abs(arr[i][colIndex]) < minAbsVal) {
            minAbsVal = std::abs(arr[i][colIndex]);
            minAbsRowIndex = i;
        }
    }
    
    arr[minAbsRowIndex][colIndex] *= -1;
}

void replaceMinAbsInEachColumn(int** arr, const size_t rows, const size_t cols) {
    for (size_t j = 0; j < cols; ++j) {
        processColumnMinAbs(arr, rows, j);
    }
}

int findOverallMax(int** arr, const size_t rows, const size_t cols) {
    if (rows == 0 || cols == 0) {
        return std::numeric_limits<int>::min();
    }
    int maxVal = arr[0][0];

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (arr[i][j] > maxVal) {
                maxVal = arr[i][j];
            }
        }
    }
    return maxVal;
}

bool rowContainsValue(const int* row, const size_t cols, const int value) {
    for (size_t j = 0; j < cols; ++j) {
        if (row[j] == value) {
            return true;
        }
    }
    return false;
}

int** deleteRowsContainingMax(int** arr, const size_t rows, const size_t cols, size_t& newRows) {
    if (rows == 0 || cols == 0) {
        newRows = 0;
        return nullptr;
    }

    const int maxValue = findOverallMax(arr, rows, cols);
    std::vector<size_t> rowsToKeep;

    for (size_t i = 0; i < rows; ++i) {
        if (!rowContainsValue(arr[i], cols, maxValue)) {
            rowsToKeep.push_back(i);
        }
    }

    newRows = rowsToKeep.size();
    if (newRows == 0) {
        return nullptr;
    }

    int** newArr = createArray(newRows, cols);
    for (size_t i = 0; i < newRows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            newArr[i][j] = arr[rowsToKeep[i]][j];
        }
    }

    return newArr;
}

int inputInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка: Введите целое число.\n" << prompt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

int inputIntInRange(const std::string& prompt, const int min, const int max) {
    int value;
    while (true) {
        value = inputInt(prompt);
        if (value >= min && value <= max) {
            return value;
        }
        std::cout << "Ошибка: Число должно быть в диапазоне от " << min << " до " << max << ".\n";
    }
}

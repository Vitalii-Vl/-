#include <iostream>
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 
#include <limits>
#include <cmath> 



/**
 * @brief Создает динамический двумерный массив заданных размеров.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Указатель на указатель (int**), представляющий созданный массив.
 */
int** createArray(int rows, int cols);

/**
 * @brief Освобождает память, выделенную для двумерного массива.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк в массиве.
 */
void deleteArray(int** arr, int rows);

/**
 * @brief Заполняет массив случайными целыми числами в заданном диапазоне.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void fillArrayRandom(int** arr, int rows, int cols);

/**
 * @brief Заполняет массив целыми числами, вводимыми с клавиатуры.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void fillArrayKeyboard(int** arr, int rows, int cols);

/**
 * @brief Предлагает пользователю выбрать способ заполнения массива (случайно или с клавиатуры).
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void chooseFillMethod(int** arr, int rows, int cols);

/**
 * @brief Выводит содержимое двумерного массива на консоль.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void printArray(int** arr, int rows, int cols);

/**
 * @brief Находит минимальный по модулю элемент в заданном столбце и заменяет его на противоположный.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param colIndex Индекс столбца, который нужно обработать.
 */
void processColumnMinAbs(int** arr, int rows, int colIndex);

/**
 * @brief Проходит по каждому столбцу массива и заменяет минимальный по модулю элемент в нем на противоположный.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 */
void replaceMinAbsInEachColumn(int** arr, int rows, int cols);

/**
 * @brief Находит максимальный элемент во всем массиве.
 * @param arr Указатель на указатель на массив.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Максимальное значение в массиве.
 */
int findOverallMax(int** arr, int rows, int cols);

/**
 * @brief Проверяет, содержит ли заданная строка массива определенное значение.
 * @param row Указатель на массив (строку).
 * @param cols Количество столбцов в строке.
 * @param value Значение для поиска.
 * @return true, если строка содержит значение, false в противном случае.
 */
bool rowContainsValue(int* row, int cols, int value);

/**
 * @brief Удаляет все строки, содержащие максимальный элемент массива.
 * @param arr Ссылка на указатель на указатель на массив (может быть изменен).
 * @param rows Ссылка на количество строк (может быть изменено).
 * @param cols Количество столбцов.
 */
void deleteRowsContainingMax(int**& arr, int& rows, int cols);


int main() {
    srand(static_cast<unsigned int>(time(0)));

    int n, m;
    do {
        std::cout << "Введите количество строк N: ";
        std::cin >> n;
        if (std::cin.fail() || n <= 0) {
            std::cout << "Ошибка: N должно быть положительным целым числом." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (n <= 0);

    do {
        std::cout << "Введите количество столбцов M: ";
        std::cin >> m;
        if (std::cin.fail() || m <= 0) {
            std::cout << "Ошибка: M должно быть положительным целым числом." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (m <= 0);

    int** matrix = createArray(n, m);

    chooseFillMethod(matrix, n, m);

    std::cout << "\n--- Исходный массив ---" << std::endl;
    printArray(matrix, n, m);

 
    std::cout << "\n--- Выполнение Задачи 1: Замена мин. по модулю в каждом столбце ---" << std::endl;
    replaceMinAbsInEachColumn(matrix, n, m);
    std::cout << "Массив после Задачи 1:" << std::endl;
    printArray(matrix, n, m);

    std::cout << "\n--- Выполнение Задачи 2: Удаление строк, содержащих максимальные элементы ---" << std::endl;
    deleteRowsContainingMax(matrix, n, m); 

    std::cout << "Массив после Задачи 2:" << std::endl;
    if (n > 0) { 
        printArray(matrix, n, m);
    } else {
        std::cout << "Все строки были удалены." << std::endl;
    }

    deleteArray(matrix, n); 

    return 0;
}


int** createArray(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
    }
    return arr;
}

void deleteArray(int** arr, int rows) {
    if (arr == nullptr) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i]; 
    }
    delete[] arr;
    arr = nullptr;
}

void fillArrayRandom(int** arr, int rows, int cols) {
    const int MIN_VAL = -100;
    const int MAX_VAL = 100;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = rand() % (MAX_VAL - MIN_VAL + 1) + MIN_VAL;
        }
    }
}

void fillArrayKeyboard(int** arr, int rows, int cols) {
    std::cout << "Пожалуйста, введите элементы массива:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        std::cout << "Строка " << i + 1 << ":" << std::endl;
        for (int j = 0; j < cols; ++j) {
            int value;
            while (true) {
                std::cout << "Элемент [" << i << "][" << j << "]: ";
                std::cin >> value;
                if (std::cin.fail()) {
                    std::cout << "Ошибка: Введите целое число." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    arr[i][j] = value;
                    break;
                }
            }
        }
    }
}

void chooseFillMethod(int** arr, int rows, int cols) {
    char choice;
    do {
        std::cout << "Как заполнить массив? (R - случайными числами, K - с клавиатуры): ";
        std::cin >> choice;
        choice = toupper(choice); 
        if (choice != 'R' && choice != 'K') {
            std::cout << "Неверный выбор. Пожалуйста, введите 'R' или 'K'." << std::endl;
        }
    } while (choice != 'R' && choice != 'K');

    if (choice == 'R') {
        fillArrayRandom(arr, rows, cols);
    } else { // choice == 'K'
        fillArrayKeyboard(arr, rows, cols);
    }
}

void printArray(int** arr, int rows, int cols) {
    if (arr == nullptr || rows == 0 || cols == 0) {
        std::cout << "Массив пуст или некорректных размеров." << std::endl;
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(5) << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void processColumnMinAbs(int** arr, int rows, int colIndex) {
    if (rows == 0) return; 

    int minAbsVal = std::abs(arr[0][colIndex]);
    int minAbsRowIndex = 0;

    for (int i = 1; i < rows; ++i) {
        if (std::abs(arr[i][colIndex]) < minAbsVal) {
            minAbsVal = std::abs(arr[i][colIndex]);
            minAbsRowIndex = i;
        }
    }
   
    arr[minAbsRowIndex][colIndex] *= -1;
}

void replaceMinAbsInEachColumn(int** arr, int rows, int cols) {
    for (int j = 0; j < cols; ++j) {
        processColumnMinAbs(arr, rows, j); 
    }
}

int findOverallMax(int** arr, int rows, int cols) {
    if (rows == 0 || cols == 0) {
        return std::numeric_limits<int>::min(); 
    }
    int maxVal = arr[0][0]; 

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arr[i][j] > maxVal) {
                maxVal = arr[i][j];
            }
        }
    }
    return maxVal;
}

bool rowContainsValue(int* row, int cols, int value) {
    for (int j = 0; j < cols; ++j) {
        if (row[j] == value) {
            return true;
        }
    }
    return false;
}

void deleteRowsContainingMax(int**& arr, int& rows, int cols) {
    if (rows == 0 || cols == 0) {
        std::cout << "Массив пуст, нет строк для удаления." << std::endl;
        return;
    }

    int maxValue = findOverallMax(arr, rows, cols);

    bool* rowsToKeep = new bool[rows];
    int newRowsCount = 0;

    for (int i = 0; i < rows; ++i) {
        if (!rowContainsValue(arr[i], cols, maxValue)) {
            rowsToKeep[i] = true;
            newRowsCount++;
        } else {
            rowsToKeep[i] = false;
        }
    }

    if (newRowsCount == 0) {
        deleteArray(arr, rows);
        arr = nullptr; 
        rows = 0; 
        delete[] rowsToKeep;
        return;
    }

   
    int** newArr = createArray(newRowsCount, cols);
    int currentRowInNewArr = 0;

    for (int i = 0; i < rows; ++i) {
        if (rowsToKeep[i]) {
            for (int j = 0; j < cols; ++j) {
                newArr[currentRowInNewArr][j] = arr[i][j];
            }
            currentRowInNewArr++;
        }
    }


    deleteArray(arr, rows);

    arr = newArr;
    rows = newRowsCount;

    delete[] rowsToKeep;
}

#include <iostream> 
#include <iomanip> 
#include <ctime> 
#include <cstdlib> 
#include <limits> 
#include <algorithm>


using namespace std;


enum FillChoice {
    RANDOM_FILL = 5, /**< Заполнение массива случайными числами. */
    MANUAL_FILL = 6 /**< Заполнение массива вручную с клавиатуры. */
};

/**
 * @brief Безопасно считывает целое число с клавиатуры.
 * @return Считанное целое число.
 */
int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Ошибка ввода! Введено некорректное значение. Программа будет завершена." << endl;
        // Сброс флагов ошибки и очистка буфера для предотвращения зацикливания
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        abort(); // Аварийное завершение программы
    }
    return value;
}

/**
 * @brief Получает размерность (m или n) от пользователя.
 * Запрашивает у пользователя целое число для размера и
 * вызывает checkDimension() для его валидации.
 * @return Размерность массива типа size_t.
 */
size_t getSize() {
    int dim_int = getValue(); // Считываем как int, чтобы можно было проверить на <= 0
    // Вызываем checkDimension вместо checkN, чтобы быть более общим для m и n
    if (dim_int <= 0) {
        cout << "Ошибка: Размерность массива должна быть больше нуля. Программа будет завершена." << endl;
        abort();
    }
    return static_cast<size_t>(dim_int); // Преобразуем к size_t
}

/**
 * @brief Создает новый динамический двумерный массив (матрицу).
 * Выделяет память для матрицы размером m строк и n столбцов.
 * @param m Количество строк.
 * @param n Количество столбцов.
 * @return Указатель на новый двумерный массив. Возвращает nullptr, если выделение памяти не удалось.
 */
int** getNewArray(const size_t m, const size_t n) {
    if (m == 0 || n == 0) return nullptr; // Обработка нулевых размеров

    int** array = new (std::nothrow) int*[m]; // Выделение памяти под указатели на строки
    if (array == nullptr) {
        cout << "Ошибка выделения памяти для строк." << endl;
        abort();
    }

    for (size_t i = 0; i < m; ++i) {
        array[i] = new (std::nothrow) int[n]; // Выделение памяти под столбцы в каждой строке
        if (array[i] == nullptr) {
            cout << "Ошибка выделения памяти для столбца " << i << "." << endl;
            // Освобождаем уже выделенную память, чтобы избежать утечек
            for (size_t k = 0; k < i; ++k) {
                delete[] array[k];
            }
            delete[] array;
            abort();
        }
    }
    return array;
}

/**
 * @brief Выводит элементы двумерного массива на экран.
 * Каждый элемент выводится с форматированием setw(6) для выравнивания.
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 */
void printArray(int** array, const size_t m, const size_t n) {
    if (array == nullptr || m == 0 || n == 0) {
        cout << "Массив пуст или некорректен для вывода." << endl;
        return;
    }
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            cout << setw(6) << array[i][j];
        }
        cout << endl;
    }
}

/**
 * @brief Заполняет двумерный массив случайными числами.
 * Числа генерируются в заданном диапазоне [start, end].
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 * @param start Нижняя граница диапазона случайных чисел.
 * @param end Верхняя граница диапазона случайных чисел.
 */
void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end) {
    // Инициализация генератора случайных чисел один раз
    // static_cast<unsigned int>(time(0)) обеспечивает разную последовательность чисел при каждом запуске
    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            // Генерация числа в диапазоне [start, end]
            array[i][j] = rand() % (end - start + 1) + start;
        }
    }
    cout << "Массив заполнен случайными числами в диапазоне [" << start << ", " << end << "]." << endl;
}

/**
 * @brief Заполняет двумерный массив числами, введенными с клавиатуры.
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 */
void fillArray(int** array, const size_t m, const size_t n) {
    if (array == nullptr || m == 0 || n == 0) {
        cout << "Массив пуст или некорректен для заполнения." << endl;
        return;
    }
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            cout << "Введите array[" << i << "][" << j << "] = ";
            array[i][j] = getValue(); // Используем безопасное считывание
        }
    }
}

/**
 * @brief Находит индекс максимального элемента в одномерном массиве (строке).
 * @param row Указатель на одномерный массив (строку).
 * @param n Размер одномерного массива (количество столбцов).
 * @return Индекс максимального элемента. Если массив пуст, возвращает 0.
 */
size_t getMaxIndexInLine(int* row, const size_t n) {
    if (n == 0) return 0; // Пустая строка

    size_t maxIndex = 0;
    for (size_t i = 1; i < n; ++i) {
        if (row[i] > row[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

/**
 * @brief Умножает максимальный элемент в каждой строке двумерного массива на 5.
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 */
void changeMaxElementInLine(int** array, const size_t m, const size_t n) {
    if (array == nullptr || m == 0 || n == 0) {
        cout << "Массив пуст или некорректен для изменения." << endl;
        return;
    }
    for (size_t i = 0; i < m; ++i) {
        size_t maxIndex = getMaxIndexInLine(array[i], n);
        array[i][maxIndex] *= 5;
    }
    cout << "Максимальный элемент в каждой строке был умножен на 5." << endl;
}

/**
 * @brief Освобождает динамически выделенную память для двумерного массива.
 * @param array Указатель на двумерный массив, который нужно удалить.
 * @param m Количество строк массива.
 */
void deleteArray(int** array, const size_t m, const size_t n) {
    if (array == nullptr) return; // Ничего удалять, если указатель нулевой

    for (size_t i = 0; i < m; ++i) {
        delete[] array[i]; // Освобождаем память для каждого столбца
    }
    delete[] array; // Освобождаем память для массива указателей
    // Примечание: Указатель array в вызывающей функции не будет обнулен,
    // так как он передан по значению. Вызывающая функция должна обнулить его вручную.
}

/**
 * @brief Создает и возвращает копию двумерного массива.
 * Выделяет новую память и копирует все элементы из исходного массива.
 * @param sourceArray Указатель на исходный двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 * @return Указатель на новый двумерный массив, являющийся копией исходного.
 * Возвращает nullptr, если исходный массив пуст или некорректен.
 */
int** copyArray(int** sourceArray, const size_t m, const size_t n) {
    if (sourceArray == nullptr || m == 0 || n == 0) {
        cout << "Невозможно скопировать пустой или некорректный массив." << endl;
        return nullptr;
    }

    int** copy = getNewArray(m, n); // Создаем новый массив того же размера
    if (copy == nullptr) {
        cout << "Ошибка при создании копии массива." << endl;
        return nullptr;
    }

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            copy[i][j] = sourceArray[i][j]; // Копируем элементы
        }
    }
    return copy;
}

/**
 * @brief Находит минимальный отрицательный элемент во всем двумерном массиве.
 * Если отрицательных элементов нет, возвращает INT_MAX (максимальное значение int).
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 * @return Минимальный отрицательный элемент или INT_MAX, если таковых нет.
 */
int findMinNegative(int** array, const size_t m, const size_t n) {
    if (array == nullptr || m == 0 || n == 0) return numeric_limits<int>::max();

    int min_neg = numeric_limits<int>::max(); // Инициализация максимальным значением int
    bool found_negative = false;

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (array[i][j] < 0) {
                if (!found_negative || array[i][j] < min_neg) {
                    min_neg = array[i][j];
                    found_negative = true;
                }
            }
        }
    }
    return min_neg;
}

/**
 * @brief Подсчитывает количество вхождений минимального отрицательного элемента.
 * Сначала находит минимальный отрицательный элемент с помощью findMinNegative().
 * Затем подсчитывает, сколько раз этот элемент встречается в массиве.
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 * @return Количество вхождений минимального отрицательного элемента.
 * Если отрицательных элементов нет, возвращает 0.
 */
int getCountOfMinNegative(int** array, const size_t m, const size_t n) {
    if (array == nullptr || m == 0 || n == 0) return 0;

    int min_val = findMinNegative(array, m, n);

    // Если findMinNegative вернул INT_MAX, значит отрицательных элементов нет
    if (min_val == numeric_limits<int>::max()) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (array[i][j] == min_val) {
                count++;
            }
        }
    }
    return count;
}

/**
 * @brief Добавляет новые столбцы к массиву, заполняя их значением минимального отрицательного элемента.
 * Создает новый массив (newArray) с расширенным количеством столбцов.
 * Копирует элементы из sourceArray и заполняет добавленные столбцы
 * значением, полученным из findMinNegative() от sourceArray.
 * @param sourceArray Указатель на исходный двумерный массив.
 * @param m Количество строк.
 * @param original_n Исходное количество столбцов.
 * @param newArray Указатель на новый, уже выделенный двумерный массив с расширенным количеством столбцов.
 * @param new_total_n Общее количество столбцов в новом массиве (original_n + количество новых столбцов).
 */
void addNewColumns(int** sourceArray, const size_t m, const size_t original_n,
                   int** newArray, const size_t new_total_n) {
    if (sourceArray == nullptr || newArray == nullptr || m == 0 || original_n == 0 || new_total_n < original_n) {
        cout << "Ошибка: Некорректные параметры для добавления столбцов." << endl;
        return;
    }

    int min_neg_val = findMinNegative(sourceArray, m, original_n);

    for (size_t i = 0; i < m; ++i) {
        // Копируем существующие элементы
        for (size_t j = 0; j < original_n; ++j) {
            newArray[i][j] = sourceArray[i][j];
        }
        // Заполняем новые столбцы
        for (size_t j = original_n; j < new_total_n; ++j) {
            newArray[i][j] = min_neg_val;
        }
    }
    cout << "Добавлены новые столбцы, заполненные значением минимального отрицательного элемента (" << min_neg_val << ")." << endl;
}

/**
 * @brief Находит значение первого отрицательного элемента в массиве.
 * Итерирует по массиву построчно, слева направо, сверху вниз.
 * @param array Указатель на двумерный массив.
 * @param m Количество строк.
 * @param n Количество столбцов.
 * @return Значение первого отрицательного элемента. Если отрицательных
 * элементов нет, возвращает 0.
 */
int findFirstNegative(int** array, const size_t m, const size_t n) {
    if (array == nullptr || m == 0 || n == 0) return 0;
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (array[i][j] < 0) {
                return array[i][j];
            }
        }
    }
    return 0;
}


/**
 * @brief Точка входа в программу.
 * Управляет выполнением программы: запрашивает размеры матрицы,
 * выделяет память, заполняет массив, выполняет операции с ним
 * и выводит результаты. Освобождает выделенную память.
 * @return 0 в случае успешного выполнения.
 */
int main() {
    setlocale(LC_ALL, "Russian"); // Установка русской локали для корректного вывода текста

   
    cout << "Введите количество строк (m): ";
    size_t m = getSize();
    cout << "Введите количество столбцов (n): ";
    size_t n = getSize();

    // 2. Создание исходного массива
    int** array = getNewArray(m, n);
    if (array == nullptr) { // Проверка на случай ошибки выделения памяти
        return 1;
    }

    cout << "Введите способ заполнения массива: " << MANUAL_FILL << " (вручную), "
         << RANDOM_FILL << " (случайными числами): ";
    int choice = getValue();

    switch (choice) {
        case RANDOM_FILL:
            int start_range, end_range;
            cout << "Введите нижнюю границу диапазона случайных чисел: ";
            start_range = getValue();
            cout << "Введите верхнюю границу диапазона случайных чисел: ";
            end_range = getValue();
            fillRandom(array, m, n, start_range, end_range);
            break;
        case MANUAL_FILL:
            fillArray(array, m, n);
            break;
        default:
            cout << "Некорректный выбор способа заполнения. Программа будет завершена." << endl;
            deleteArray(array, m, n); // Освобождаем выделенную память перед выходом
            return 1;
    }

    
    cout << "\nИсходный массив:" << endl;
    printArray(array, m, n);

    cout << "\n--- Операция: Умножение максимальных элементов в строках на 5 ---" << endl;
    int** arrayCopy = copyArray(array, m, n);
    if (arrayCopy == nullptr) { // Проверка на случай ошибки копирования
        deleteArray(array, m, n);
        return 1;
    }
    changeMaxElementInLine(arrayCopy, m, n);
    cout << "Массив после изменения (копия):" << endl;
    printArray(arrayCopy, m, n);
    deleteArray(arrayCopy, m, n); // Освобождаем память копии

  
    cout << "\n--- Операция: Добавление новых столбцов ---" << endl;
    int count_min_neg = getCountOfMinNegative(array, m, n);
    size_t new_n = n + count_min_neg; // Новое количество столбцов

    cout << "Минимальный отрицательный элемент в исходном массиве встречается " << count_min_neg << " раз(а)." << endl;

    if (count_min_neg > 0) {
        int** resultArray = getNewArray(m, new_n); // Создаем новый массив с увеличенным размером
        if (resultArray == nullptr) { // Проверка на случай ошибки выделения памяти
            deleteArray(array, m, n);
            return 1;
        }
        addNewColumns(array, m, n, resultArray, new_n); // Добавляем столбцы
        cout << "Массив после добавления столбцов:" << endl;
        printArray(resultArray, m, new_n);
        deleteArray(resultArray, m, new_n); // Освобождаем память результирующего массива
    } else {
        cout << "Отрицательных элементов или их повторений нет, новые столбцы не добавлены." << endl;
    }

    deleteArray(array, m, n);
    array = nullptr; // Обнуляем указатель после освобождения памяти

    return 0; // Успешное завершение программы
}

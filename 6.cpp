#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <string>

using namespace std;

/**
 * @brief Режимы заполнения массива
 */
enum class FillMode {
};

/**
 * @brief Отображает элементы массива на консоль.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void displayArray(const int* arr, const size_t size);

/**
 * @brief Заполняет массив в соответствии с выбранным режимом.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 * @param mode Режим заполнения (RANDOM или MANUAL).
 * @param left Левая граница диапазона для случайного заполнения.
 * @param right Правая граница диапазона для случайного заполнения.
 */
void fillArray(int* const arr, const size_t size, FillMode mode, int left, int right);

/**
 * @brief Вычисляет сумму всех четных элементов массива.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 * @return Сумма четных элементов массива.
 */
long long calculateSumOfEvenElements(const int* arr, const size_t size);

/**
 * @brief Подсчитывает количество элементов массива, значения которых состоят из двух цифр.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 * @return Количество двухзначных чисел в массиве.
 */
int countTwoDigitNumbers(const int* arr, const size_t size);

/**
 * @brief Заменяет последний отрицательный элемент массива на модуль первого элемента массива.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void replaceLastNegativeElement(int* arr, const size_t size);

/**
 * @brief Ввод целого числа с проверкой
 * @param prompt Приглашение для ввода
 * @return Введенное целое число
 */
int inputInt(const string& prompt);

/**
 * @brief Ввод размера массива с проверкой
 * @param prompt Приглашение для ввода
 * @return Введенный размер массива
 */
size_t inputSize(const string& prompt);

/**
 * @brief Ввод символа выбора режима заполнения
 * @param prompt Приглашение для ввода
 * @return Введенный символ (R/r или M/m)
 */
char inputMode(const string& prompt);

int main() {
    const size_t n = inputSize("Введите размер массива (n): ");
    
    int* myArray = new int[n];
    if (myArray == nullptr) {
        cerr << "Ошибка: Не удалось выделить память под массив.\n";
        return 1;
    }

    const int left = inputInt("Введите левую границу диапазона: ");
    const int right = inputInt("Введите правую границу диапазона: ");

    char choice = inputMode("Как заполнить массив? (R - случайно, M - вручную): ");
    FillMode mode = (choice == 'R' || choice == 'r') ? FillMode::RANDOM : FillMode::MANUAL;

    fillArray(myArray, n, mode, left, right);
    cout << "\nМассив заполнен:\n";
    displayArray(myArray, n);

    const long long sumEven = calculateSumOfEvenElements(myArray, n);
    cout << "\n1. Сумма четных элементов: " << sumEven << endl;
    
    const int twoDigitCount = countTwoDigitNumbers(myArray, n);
    cout << "2. Количество элементов с двумя цифрами: " << twoDigitCount << endl;

    if (n > 0) {
        cout << "\n3. Выполняется замена последнего отрицательного элемента...\n";
        replaceLastNegativeElement(myArray, n);
        cout << "Массив после возможной замены:\n";
        displayArray(myArray, n);
    } else {
        cout << "\n3. Массив пуст, замена элемента невозможна.\n";
    }

    delete[] myArray;
    myArray = nullptr;

    return 0;
}

size_t inputSize(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    while (cin.fail() || value <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некорректный ввод. Пожалуйста, введите положительное целое число: ";
        cin >> value;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return static_cast<size_t>(value);
}

int inputInt(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
        cin >> value;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

char inputMode(const string& prompt) {
    char c;
    cout << prompt;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (c != 'R' && c != 'r' && c != 'M' && c != 'm') {
        cout << "Некорректный ввод. Пожалуйста, введите R или M: ";
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return c;
}

void displayArray(const int* arr, const size_t size) {
    if (arr == nullptr || size == 0) {
        cout << "Массив пуст или некорректен для отображения.\n";
        return;
    }
    cout << "Массив: [";
    for (size_t i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void fillArray(int* const arr, const size_t size, FillMode mode, int left, int right) {
    if (arr == nullptr || size == 0) {
        return;
    }
    
    if (mode == FillMode::RANDOM) {
        srand(static_cast<unsigned>(time(nullptr)));
        for (size_t i = 0; i < size; ++i) {
            arr[i] = left + rand() % (right - left + 1);
        }
    } else {
        cout << "Пожалуйста, введите " << size << " целых чисел:\n";
        for (size_t i = 0; i < size; ++i) {
            arr[i] = inputInt("Элемент [" + to_string(i) + "]: ");
        }
    }
}

long long calculateSumOfEvenElements(const int* arr, const size_t size) {
    long long sum = 0;
    if (arr == nullptr || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

int countTwoDigitNumbers(const int* arr, const size_t size) {
    int count = 0;
    if (arr == nullptr || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; ++i) {
        if ((abs(arr[i]) >= 10) && (abs(arr[i]) <= 99)) {
            count++;
        }
    }
    return count;
}

void replaceLastNegativeElement(int* arr, const size_t size) {
    if (arr == nullptr || size == 0) {
        cout << "Массив пуст или некорректен. Замена невозможна.\n";
        return;
    }
    
    const int firstElementAbsoluteValue = abs(arr[0]);
    int lastNegativeIndex = -1;

    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        if (arr[i] < 0) {
            lastNegativeIndex = i;
            break;
        }
    }

    if (lastNegativeIndex != -1) {
        cout << "Найден последний отрицательный элемент по индексу " << lastNegativeIndex
             << " (значение: " << arr[lastNegativeIndex] << ").\n";
        cout << "Заменяем его на модуль первого элемента: " << firstElementAbsoluteValue << ".\n";
        arr[lastNegativeIndex] = firstElementAbsoluteValue;
    } else {
        cout << "Отрицательные элементы в массиве не найдены. Замена не произведена.\n";
    }
}

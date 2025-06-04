#include <iostream> 
#include <ctime> 
#include <cstdlib> 
#include <limits> 


/**
 * @brief Отображает элементы массива на консоль.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void displayArray(const int* arr, const int size);

/**
 * @brief Заполняет массив случайными целыми числами в заданном диапазоне.
 * Перед первым использованием rand() необходимо вызвать srand() один раз.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 * @param minVal Минимальное возможное значение элемента (включительно).
 * @param maxVal Максимальное возможное значение элемента (включительно).
 */
void fillArrayRandom(int* arr, int size, int minVal, int maxVal);

/**
 * @brief Заполняет массив числами, введенными пользователем с клавиатуры.
 * Содержит проверку ввода для обеспечения корректности данных.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void fillArrayManual(int* arr, int size);

/**
 * @brief Вычисляет сумму всех четных элементов массива.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 * @return Сумма четных элементов массива.
 */
long long calculateSumOfEvenElements(const int* arr, const int size);

/**
 * @brief Подсчитывает количество элементов массива, значения которых состоят из двух цифр.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 * @return Количество двухзначных чисел в массиве.
 */
int countTwoDigitNumbers(const int* arr, const int size);

/**
 * @brief Заменяет последний отрицательный элемент массива на модуль первого элемента массива.
 * @param arr Указатель на первый элемент массива.
 * @param size Размер массива.
 */
void replaceLastNegativeElement(int* arr, int size);

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int n; 
    std::cout << "Введите размер массива (n): ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Некорректный ввод. Размер массива должен быть положительным целым числом.\n";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите размер массива (n): ";
    }

    int* myArray = new int[n];

    if (myArray == nullptr) {
        std::cerr << "Ошибка: Не удалось выделить память под массив.\n";
        return 1; 
    }

    char choice;
    std::cout << "Как заполнить массив? (S - случайно, K - с клавиатуры): ";
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    if (choice == 'S' || choice == 's') {
        // Заполнение случайными числами в диапазоне [-1000; 1000]
        fillArrayRandom(myArray, n, -1000, 1000); 
        std::cout << "\nМассив заполнен случайными числами:\n";
    } else if (choice == 'K' || choice == 'k') {
        fillArrayManual(myArray, n);
        std::cout << "\nМассив заполнен с клавиатуры:\n";
    } else {
        std::cout << "Некорректный выбор. Массив будет заполнен случайными числами по умолчанию.\n";
        fillArrayRandom(myArray, n, -1000, 1000);
        std::cout << "\nМассив заполнен случайными числами:\n";
    }
    
    displayArray(myArray, n);


    long long sumEven = calculateSumOfEvenElements(myArray, n);
    std::cout << "\n1. Сумма четных элементов: " << sumEven << std::endl;
    
    int twoDigitCount = countTwoDigitNumbers(myArray, n);
    std::cout << "2. Количество элементов с двумя цифрами: " << twoDigitCount << std::endl;

    if (n > 0) { 
        std::cout << "\n3. Выполняется замена последнего отрицательного элемента...\n";
        replaceLastNegativeElement(myArray, n);
        std::cout << "Массив после возможной замены:\n";
        displayArray(myArray, n); 
    } else {
        std::cout << "\n3. Массив пуст, замена элемента невозможна.\n";
    }

    delete[] myArray;
    myArray = nullptr; // Обнуляем указатель для предотвращения "висячих" указателей

    return 0;
}

void displayArray(const int* arr, int size) {
    if (arr == nullptr || size <= 0) {
        std::cout << "Массив пуст или некорректен для отображения.\n";
        return;
    }
    std::cout << "Массив: [";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void fillArrayRandom(int* arr, int size, int minVal, int maxVal) {
    if (arr == nullptr || size <= 0) {
        return; 
    }
    for (int i = 0; i < size; ++i) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

void fillArrayManual(int* arr, int size) {
    if (arr == nullptr || size <= 0) {
        return; 
    }
    std::cout << "Пожалуйста, введите " << size << " целых чисел:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << "Элемент [" << i << "]: ";
        while (!(std::cin >> arr[i])) {
            std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
            std::cin.clear(); // Сброс флагов ошибок
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            std::cout << "Элемент [" << i << "]: ";
        }
    }
}

long long calculateSumOfEvenElements(const int* arr, int size) {
    long long sum = 0;
    if (arr == nullptr || size <= 0) {
        return 0;
    }
    for (int i = 0; i < size; ++i) {
        if (arr[i] % 2 == 0) {
            sum += arr[i]; 
        }
    }
    return sum;
}

int countTwoDigitNumbers(const int* arr, int size) {
    int count = 0; 
    if (arr == nullptr || size <= 0) {
        return 0;
    }
    for (int i = 0; i < size; ++i) {
        if (std::abs(arr[i]) >= 10 && std::abs(arr[i]) <= 99) {
            count++; 
        }
    }
    return count;
}

void replaceLastNegativeElement(int* arr, int size) {
    if (arr == nullptr || size <= 0) {
        std::cout << "Массив пуст или некорректен. Замена невозможна.\n";
        return; 
    }
    
    int firstElementAbsoluteValue = std::abs(arr[0]); 

    int lastNegativeIndex = -1; 

    for (int i = size - 1; i >= 0; --i) {
        if (arr[i] < 0) {
            lastNegativeIndex = i;
            break; 
        }
    }

    if (lastNegativeIndex != -1) {
        std::cout << "Найден последний отрицательный элемент по индексу " << lastNegativeIndex 
                  << " (значение: " << arr[lastNegativeIndex] << ").\n";
        std::cout << "Заменяем его на модуль первого элемента: " << firstElementAbsoluteValue << ".\n";
        arr[lastNegativeIndex] = firstElementAbsoluteValue; // Производим замену
    } else {
        std::cout << "Отрицательные элементы в массиве не найдены. Замена не произведена.\n";
    }
}

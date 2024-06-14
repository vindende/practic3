#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib> // Для функции rand() и srand()
#include <cstring>
#include <cstdio>
#include <ctime> // Для функции time()
#include <fstream>
#include <iostream>

using namespace std;

// Структура для хранения данных о вкладе
struct Deposit {
    int accountNumber;
    char passportData[50];
    char depositCategory[20];
    double currentAmount;
    char lastOperationDate[20];
};

// Функция для генерации случайной даты в формате DD.MM.YY
void generateRandomDate(char* date) {
    int day = rand() % 28 + 1;     // Случайный день от 1 до 28
    int month = rand() % 12 + 1;   // Случайный месяц от 1 до 12
    int year = rand() % 21 + 2000; // Случайный год от 2000 до 2020
    sprintf(date, "%02d.%02d.%02d", day, month, year % 100); // Форматируем дату в строку
}

// Функция для генерации случайной записи о вкладе
Deposit generateRandomDeposit() {
    Deposit deposit;
    deposit.accountNumber = (rand() + 1000000) % 100000 + 1;
    sprintf_s(deposit.passportData, "%d", rand() % 1000);
    strcpy_s(deposit.depositCategory, (rand() % 2) ? "срочный" : "не срочный");
    deposit.currentAmount = (rand() + 1000000) % 1000000 / 100.0;
    generateRandomDate(deposit.lastOperationDate);
    return deposit;
}

int generate() {
    srand(static_cast<unsigned int>(
        time(nullptr))); // Инициализируем генератор случайных чисел
    const char* filename = "deposits.bin"; // Имя файла для записи

    // Открываем файл для записи в бинарном режиме
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }

    // Генерируем и записываем случайные записи
    for (int i = 0; i < 50000; i++) {
        Deposit deposit = generateRandomDeposit();
        outFile.write(reinterpret_cast<const char*>(&deposit), sizeof(Deposit));
    }

    outFile.close(); // Закрываем файл
    cout << "Файл успешно заполнен 50000 случайными записями." << endl;

    return 0;
}

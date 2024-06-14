#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib> // ��� ������� rand() � srand()
#include <cstring>
#include <cstdio>
#include <ctime> // ��� ������� time()
#include <fstream>
#include <iostream>

using namespace std;

// ��������� ��� �������� ������ � ������
struct Deposit {
    int accountNumber;
    char passportData[50];
    char depositCategory[20];
    double currentAmount;
    char lastOperationDate[20];
};

// ������� ��� ��������� ��������� ���� � ������� DD.MM.YY
void generateRandomDate(char* date) {
    int day = rand() % 28 + 1;     // ��������� ���� �� 1 �� 28
    int month = rand() % 12 + 1;   // ��������� ����� �� 1 �� 12
    int year = rand() % 21 + 2000; // ��������� ��� �� 2000 �� 2020
    sprintf(date, "%02d.%02d.%02d", day, month, year % 100); // ����������� ���� � ������
}

// ������� ��� ��������� ��������� ������ � ������
Deposit generateRandomDeposit() {
    Deposit deposit;
    deposit.accountNumber = (rand() + 1000000) % 100000 + 1;
    sprintf_s(deposit.passportData, "%d", rand() % 1000);
    strcpy_s(deposit.depositCategory, (rand() % 2) ? "�������" : "�� �������");
    deposit.currentAmount = (rand() + 1000000) % 1000000 / 100.0;
    generateRandomDate(deposit.lastOperationDate);
    return deposit;
}

int generate() {
    srand(static_cast<unsigned int>(
        time(nullptr))); // �������������� ��������� ��������� �����
    const char* filename = "deposits.bin"; // ��� ����� ��� ������

    // ��������� ���� ��� ������ � �������� ������
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "�� ������� ������� ���� ��� ������." << endl;
        return 1;
    }

    // ���������� � ���������� ��������� ������
    for (int i = 0; i < 50000; i++) {
        Deposit deposit = generateRandomDeposit();
        outFile.write(reinterpret_cast<const char*>(&deposit), sizeof(Deposit));
    }

    outFile.close(); // ��������� ����
    cout << "���� ������� �������� 50000 ���������� ��������." << endl;

    return 0;
}

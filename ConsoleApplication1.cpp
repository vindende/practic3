#include "random generate.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

// Структура для хранения данных о вкладе
struct Deposit {
    int accountNumber;
    char passportData[50];
    char depositCategory[20];
    double currentAmount;
    char lastOperationDate[20];
};

// Узел двусвязного списка
struct Node {
    Deposit* data;
    Node* prev;
    Node* next;
};

// Функция для добавления элемента в конец списка
void addToEnd(Node*& head, Deposit* deposit) {
    Node* newNode = new Node;
    newNode->data = deposit;
    newNode->next = NULL;

    if (head == NULL) { // список пустой
        newNode->prev = NULL;
        head = newNode;
        return;
    }

    Node* lastNode = head;
    while (lastNode->next != NULL) { // идем до конца списка пока не встретим NULL
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
    newNode->prev = lastNode;
}

// Функция для включения элемента в упорядоченный список
void insertInOrder(Node*& head, Deposit* deposit) {
    Node* newNode = new Node;
    newNode->data = deposit;

    if (head == NULL || strcmp(deposit->depositCategory, head->data->depositCategory) < 0) {
        newNode->prev = NULL;
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != NULL && strcmp(deposit->depositCategory, current->next->data->depositCategory) >= 0) {
        current = current->next;
    }

    newNode->prev = current;
    newNode->next = current->next;
    if (current->next != NULL) {
        current->next->prev = newNode;
    }
    current->next = newNode;
}

// Функция для удаления произвольного элемента списка
void removeNode(Node*& head, Node* nodeToRemove) {
    if (head == NULL || nodeToRemove == NULL) {
        return;
    }

    if (head == nodeToRemove) {
        head = nodeToRemove->next;
    }

    if (nodeToRemove->next != NULL) {
        nodeToRemove->next->prev = nodeToRemove->prev;
    }

    if (nodeToRemove->prev != NULL) {
        nodeToRemove->prev->next = nodeToRemove->next;
    }

    delete nodeToRemove->data;
    delete nodeToRemove;
}

// Функция для вывода списка на экран в прямом направлении
void printListForward(Node* head) {
    if (head == NULL) {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current = head;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(13) << "Номер счета";
    cout << setw(23) << "Паспортные данные";
    cout << setw(20) << "Категория вклада";
    cout << setw(22) << "Текущая сумма вклада";
    cout << setw(25) << "Дата последней операции";
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    while (current != NULL) {
        cout << setw(10) << current->data->accountNumber
            << setw(19) << current->data->passportData
            << setw(24) << current->data->depositCategory
            << setw(18) << current->data->currentAmount
            << setw(24) << current->data->lastOperationDate;
        current = current->next;
        cout << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

// Функция для вывода списка на экран в обратном направлении
void printListBackward(Node* head) {
    if (head == NULL) {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(13) << "Номер счета";
    cout << setw(23) << "Паспортные данные";
    cout << setw(20) << "Категория вклада";
    cout << setw(22) << "Текущая сумма вклада";
    cout << setw(25) << "Дата последней операции";
    cout << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    while (current != NULL) {
        cout << setw(10) << current->data->accountNumber
            << setw(19) << current->data->passportData
            << setw(24) << current->data->depositCategory
            << setw(18) << current->data->currentAmount
            << setw(24) << current->data->lastOperationDate;
        current = current->prev;
        cout << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

// Функция для сохранения списка в файл
void saveListToFile(Node* head, const char* fileName) {
    ofstream file(fileName, ios::binary);
    if (!file) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    Node* current = head;
    while (current != NULL) {
        file.write(reinterpret_cast<char*>(current->data), sizeof(Deposit));
        current = current->next;
    }

    file.close();
}

// Функция для загрузки списка из файла
Node* loadListFromFile(const char* fileName) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        return NULL;
    }

    Node* head = NULL;
    Deposit* deposit = new Deposit;
    while (file.read(reinterpret_cast<char*>(deposit), sizeof(Deposit))) {
        addToEnd(head, deposit);
        //cout << deposit->accountNumber << endl;
        deposit = new Deposit;
    }

    delete deposit;
    file.close();

    return head;
}

// Функция для освобождения памяти, занятой списком
void freeListMemory(Node*& head) {
    Node* current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        delete current->data;
        delete current;
        current = nextNode;
    }

    head = NULL;
}
void printInfoAndWait() {
    cout << endl;
    puts("Чтобы перейти к выбору нажмите Enter");
    do { getchar(); } while (getchar() != '\n');
}
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "russian");
    generate();
    const char* fileName;

    if (argc == 2) {
        fileName = argv[1];
    }
    else {
        cout << "Введите имя файла: ";
        char input[100];
        cin.getline(input, 100);
        fileName = input;
    }

    Node* head = loadListFromFile(fileName);

    int choice;
    do {
        system("cls");
        cout << "Главное меню" << endl;
        cout << "1. Добавить вклад" << endl;
        cout << "2. Удалить вклад" << endl;
        cout << "3. Вывести список в прямом направлении" << endl;
        cout << "4. Вывести список в обратном направлении" << endl;
        cout << "5. Вывести наибольшую сумму вклада в категории 'срочный'" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Deposit* deposit = new Deposit;
            cout << "Введите номер счета: ";
            cin >> deposit->accountNumber;
            cout << "Введите паспортные данные: ";
            cin.ignore();
            cin.getline(deposit->passportData, 50);
            cout << "Введите категорию вклада: ";
            cin.getline(deposit->depositCategory, 20);
            cout << "Введите текущую сумму вклада: ";
            cin >> deposit->currentAmount;
            cout << "Введите дату последней операции: ";
            cin.ignore();
            cin.getline(deposit->lastOperationDate, 20);

            insertInOrder(head, deposit);
            printInfoAndWait();
            break;
        }
        case 2: {
            int accountNumber;
            cout << "Введите номер счета для удаления: ";
            cin >> accountNumber;

            Node* current = head;
            while (current != NULL) {
                if (current->data->accountNumber == accountNumber) {
                    removeNode(head, current);
                    break;
                }
                current = current->next;
            }
            printInfoAndWait();
            break;
        }
        case 3: {
            cout << "Список в прямом направлении:" << endl;
            printListForward(head);
            printInfoAndWait();
            break;
        }
        case 4: {
            cout << "Список в обратном направлении:" << endl;
            printListBackward(head);
            printInfoAndWait();
            break;
        }
        case 5: {
            double maxAmount = 0;

            Node* current = head;
            while (current != NULL) {
                if (!strcmp(current->data->depositCategory, "срочный") && current->data->currentAmount > maxAmount) {
                    cout << "Сумма вклада: " << current->data->currentAmount << endl;
                    maxAmount = current->data->currentAmount;
                }
                current = current->next;
            }

            cout << "Наибольшая сумма вклада в категории 'срочный': " << maxAmount << endl;
            printInfoAndWait();
            break;
        }
        case 0: {
            saveListToFile(head, fileName);
            freeListMemory(head);
            printInfoAndWait();
            break;
        }
        default:
            cout << "Неверный выбор" << endl;
        }
    } while (choice != 0);

    return 0;
}

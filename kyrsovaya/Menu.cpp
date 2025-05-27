#include "Menu.h"
#include <iostream>
#include <string>
#include <limits>
#include <locale>

int Menu::mainMenu() {
    int choice;
    do {
        std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n"
            << "1. Совершить платеж\n"
            << "2. Управление операторами\n"
            << "3. Просмотр истории платежей\n"
            << "4. Выход\n"
            << "Выберите пункт: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число от 1 до 4\n";
            continue;
        }
        break;
    } while (true);

    return choice;
}

int Menu::paymentMenu() {
    int choice;
    do {
        std::cout << "\n=== МЕНЮ ПЛАТЕЖА ===\n"
            << "1. Выбрать оператора\n"
            << "2. Ввести номер телефона\n"
            << "3. Ввести сумму\n"
            << "4. Подтвердить платеж\n"
            << "5. Вернуться назад\n"
            << "Выберите пункт: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число от 1 до 5\n";
            continue;
        }
        break;
    } while (true);

    return choice;
}

int Menu::operatorMenu() {
    int choice;
    do {
        std::cout << "\n=== УПРАВЛЕНИЕ ОПЕРАТОРАМИ ===\n"
            << "1. Добавить оператора\n"
            << "2. Удалить оператора\n"
            << "3. Просмотреть список\n"
            << "4. Вернуться назад\n"
            << "Выберите пункт: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Введите число от 1 до 4\n";
            continue;
        }
        break;
    } while (true);

    return choice;
}

std::string Menu::inputPhoneNumber() {
    std::string phone;
    do {
        std::cout << "Введите номер телефона (10 цифр): ";
        std::cin >> phone;

        if (phone.length() != 10 || phone.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "Неверный формат номера! Попробуйте снова.\n";
            continue;
        }
        break;
    } while (true);

    return phone;
}

double Menu::inputAmount() {
    double amount;
    do {
        std::cout << "Введите сумму (больше 0): ";
        std::cin >> amount;

        if (std::cin.fail() || amount <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверная сумма! Попробуйте снова.\n";
            continue;
        }
        break;
    } while (true);

    return amount;
}
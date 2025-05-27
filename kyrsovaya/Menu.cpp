#include "Menu.h"
#include <iostream>
#include <string>
#include <limits>
#include <locale>
#include <iomanip>

int Menu::mainMenu() {
    int choice;
    do {
        std::cout << "\n=== ������� ���� ===\n"
            << "1. ��������� ������\n"
            << "2. ���������� �����������\n"
            << "3. �������� ������� ��������\n"
            << "4. �����\n"
            << "�������� �����: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ����� �� 1 �� 4\n";
            continue;
        }
        break;
    } while (true);

    return choice;
}

int Menu::paymentMenu() {
    int choice;
    do {
        std::cout << "\n=== ���� ������� ===\n"
            << "1. ������� ���������\n"
            << "2. ������ ����� ��������\n"
            << "3. ������ �����\n"
            << "4. ����������� ������\n"
            << "5. ��������� �����\n"
            << "�������� �����: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ����� �� 1 �� 5\n";
            continue;
        }
        break;
    } while (true);

    return choice;
}

int Menu::operatorMenu() {
    int choice;
    do {
        std::cout << "\n=== ���������� ����������� ===\n"
            << "1. �������� ���������\n"
            << "2. ������� ���������\n"
            << "3. ����������� ������\n"
            << "4. ��������� �����\n"
            << "�������� �����: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������! ������� ����� �� 1 �� 4\n";
            continue;
        }
        break;
    } while (true);

    return choice;
}

std::string Menu::inputPhoneNumber() {
    std::string phone;
    do {
        std::cout << "������� ����� �������� (10 ����): ";
        std::cin >> phone;

        if (phone.length() != 10 || phone.find_first_not_of("0123456789") != std::string::npos) {
            std::cout << "�������� ������ ������! ���������� �����.\n";
            continue;
        }
        break;
    } while (true);

    return phone;
}

double Menu::inputAmount() {
    double amount;
    do {
        std::cout << "������� ����� (������ 0): ";
        std::cin >> amount;

        if (std::cin.fail() || amount <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "�������� �����! ���������� �����.\n";
            continue;
        }
        break;
    } while (true);

    return amount;
}

double Menu::acceptCash(double requiredAmount) {
    double cashReceived = 0.0;
    double remaining = requiredAmount;

    std::cout << "\n=== ��Ȩ� �������� ===\n";
    std::cout << "��������� �����: " << std::fixed << std::setprecision(2)
        << requiredAmount << " ���.\n";

    do {
        double payment;
        std::cout << "������� ����� (�������� ������: "
            << std::fixed << std::setprecision(2) << remaining << " ���.): ";
        std::cin >> payment;

        if (std::cin.fail() || payment <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "�������� �����! ���������� �����.\n";
            continue;
        }

        cashReceived += payment;
        remaining = requiredAmount - cashReceived;

        if (remaining > 0) {
            std::cout << "�������: " << std::fixed << std::setprecision(2)
                << cashReceived << " ���. �������� ������: "
                << remaining << " ���.\n";
        }
    } while (remaining > 0);

    if (cashReceived > requiredAmount) {
        double change = cashReceived - requiredAmount;
        std::cout << "�� ������ ������ ��������� �����. �����: "
            << std::fixed << std::setprecision(2) << change << " ���.\n";
    }

    std::cout << "������ �������. �������!\n";
    return cashReceived;
}
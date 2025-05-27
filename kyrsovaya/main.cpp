#include <iostream>
#include <fstream>
#include <locale>
#include <clocale>
#include "Terminal.h"
#include "Menu.h"

int main() {
    // Настройка локали для корректного отображения русского языка
    setlocale(LC_ALL, "Russian");
    std::locale::global(std::locale(""));

    Terminal terminal;

    // Загрузка операторов из файла
    std::ifstream opsFile("data/Operators.dat");
    if (opsFile.is_open()) {
        std::string line;
        while (std::getline(opsFile, line)) {
            if (!line.empty()) {
                terminal.addOperator(line);
            }
        }
        opsFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл Operators.dat!\n";
    }

    int mainChoice;
    do {
        mainChoice = Menu::mainMenu();

        switch (mainChoice) {
        case 1: { // Совершить платеж
            Payment payment;
            std::string selectedOperator;
            bool paymentCompleted = false;

            int paymentChoice;
            do {
                paymentChoice = Menu::paymentMenu();

                switch (paymentChoice) {
                case 1: { // Выбрать оператора
                    terminal.showOperators();
                    if (terminal.getOperators().empty()) {
                        std::cout << "Нет доступных операторов!\n";
                        break;
                    }

                    int opNum;
                    std::cout << "Выберите номер оператора: ";
                    std::cin >> opNum;

                    if (opNum < 1 || opNum > terminal.getOperators().size()) {
                        std::cout << "Неверный выбор!\n";
                    }
                    else {
                        selectedOperator = terminal.getOperators()[opNum - 1];
                        payment.setOperatorName(selectedOperator);
                        std::cout << "Выбран оператор: " << selectedOperator << "\n";
                    }
                    break;
                }
                case 2: { // Ввести номер телефона
                    std::string phone = Menu::inputPhoneNumber();
                    payment.setPhoneNumber(phone);
                    break;
                }
                case 3: { // Ввести сумму
                    double amount = Menu::inputAmount();
                    double commission = terminal.calculateCommission(
                        payment.getOperatorName(), amount);
                    payment.setAmount(amount);
                    payment.setCommission(commission);
                    break;
                }
                case 4: { // Подтвердить платеж
                    if (payment.getOperatorName().empty() ||
                        payment.getPhoneNumber().empty() ||
                        payment.getAmount() <= 0) {
                        std::cout << "Не все данные заполнены!\n";
                        break;
                    }

                    payment.setPaymentTime(std::time(nullptr));
                    terminal.processPayment(payment);
                    terminal.printReceipt(payment);
                    paymentCompleted = true;
                    break;
                }
                case 5: // Назад
                    break;
                }

                if (paymentCompleted) break;
            } while (paymentChoice != 5);
            break;
        }
        case 2: { // Управление операторами
            int operatorChoice;
            do {
                operatorChoice = Menu::operatorMenu();

                switch (operatorChoice) {
                case 1: { // Добавить оператора
                    std::string newOperator;
                    std::cout << "Введите название оператора: ";
                    std::cin.ignore(); // Очистка буфера перед вводом строки
                    std::getline(std::cin, newOperator);
                    terminal.addOperator(newOperator);
                    break;
                }
                case 2: { // Удалить оператора
                    terminal.showOperators();
                    if (terminal.getOperators().empty()) {
                        std::cout << "Нет операторов для удаления!\n";
                        break;
                    }

                    int opNum;
                    std::cout << "Выберите номер оператора для удаления: ";
                    std::cin >> opNum;

                    if (opNum < 1 || opNum > terminal.getOperators().size()) {
                        std::cout << "Неверный выбор!\n";
                    }
                    else {
                        std::string opToRemove = terminal.getOperators()[opNum - 1];
                        terminal.removeOperator(opToRemove);
                        std::cout << "Оператор " << opToRemove << " удален\n";
                    }
                    break;
                }
                case 3: // Просмотреть список
                    terminal.showOperators();
                    break;
                case 4: // Назад
                    break;
                }
            } while (operatorChoice != 4);
            break;
        }
        case 3: // Просмотр истории платежей
            terminal.showPaymentHistory();
            break;
        case 4: // Выход
            std::cout << "Выход из программы...\n";
            break;
        }
    } while (mainChoice != 4);
    std::cin.get();
    return 0;
}
#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>
#include "Terminal.h"
#include "Menu.h"

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul");
#ifdef _WIN32
    system("chcp 1251 > nul"); // Устанавливаем кодировку Windows-1251
#endif

    Terminal terminal;

    // Загрузка операторов с проверкой
    std::cout << "=== ЗАГРУЗКА ОПЕРАТОРОВ ===\n";
    std::ifstream opsFile("data/Operators.dat");
    if (opsFile.is_open()) {
        std::string line;
        while (std::getline(opsFile, line)) {
            if (!line.empty()) {
                terminal.addOperator(line);
                std::cout << "Загружен оператор: " << line << "\n";
            }
        }
        opsFile.close();
    }
    else {
        std::cerr << "Файл операторов не найден! Будет создан новый.\n";

        // Создаем файл с операторами по умолчанию
        std::ofstream newOpsFile("data/Operators.dat");
        if (newOpsFile) {
            newOpsFile << "МТС\nБилайн\nМегафон\nTele2\n";
            terminal.addOperator("МТС");
            terminal.addOperator("Билайн");
            terminal.addOperator("Мегафон");
            terminal.addOperator("Tele2");
        }
    }

    // Главное меню
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

                    // Приём наличных
                    double amountToPay = payment.getAmount() + payment.getCommission();
                    std::cout << "К оплате: " << std::fixed << std::setprecision(2)
                        << amountToPay << " руб. (включая комиссию)\n";

                    Menu::acceptCash(amountToPay);

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
                    std::cin.ignore();
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

    // Пауза перед завершением
    std::cout << "Нажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
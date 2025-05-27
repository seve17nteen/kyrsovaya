#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <locale>
#include "Terminal.h"
#include "Print.h"

void Terminal::addOperator(const std::string& name) {
    // Проверка на дубликат
    if (std::find(operators.begin(), operators.end(), name) == operators.end()) {
        operators.push_back(name);

        // Полная перезапись файла
        std::ofstream opsFile("data/Operators.dat");
        if (opsFile.is_open()) {
            for (const auto& op : operators) {
                opsFile << op << "\n";
            }
        }
    }
}

void Terminal::removeOperator(const std::string& name) {
    auto it = std::remove(operators.begin(), operators.end(), name);
    if (it != operators.end()) {
        operators.erase(it, operators.end());

        // Полная перезапись файла
        std::ofstream opsFile("data/Operators.dat");
        if (opsFile.is_open()) {
            for (const auto& op : operators) {
                opsFile << op << "\n";
            }
        }
    }
}

void Terminal::processPayment(const Payment& payment) {
    payments.push_back(payment);
    Payment::saveToFile(payment, "data/Payments.dat");
}

void Terminal::printReceipt(const Payment& payment) const {
    Print::printReceipt(payment);
}

void Terminal::showOperators() const {
    setlocale(LC_ALL, "Russian");
    std::cout << "\nДоступные операторы:\n";
    for (size_t i = 0; i < operators.size(); ++i) {
        std::cout << i + 1 << ". " << operators[i] << "\n";
    }
}

void Terminal::showPaymentHistory() const {
    std::ifstream file("data/Payments.dat");
    if (!file.is_open()) {
        std::cout << "\nИстория платежей пуста\n";
        return;
    }

    std::cout << "\n=== ИСТОРИЯ ПЛАТЕЖЕЙ ===\n";
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Payment payment;
        std::string token;

        if (std::getline(iss, token, '|')) payment.setOperatorName(token);
        if (std::getline(iss, token, '|')) payment.setPhoneNumber(token);
        if (std::getline(iss, token, '|')) payment.setAmount(std::stod(token));
        if (std::getline(iss, token, '|')) payment.setCommission(std::stod(token));
        if (std::getline(iss, token, '|')) payment.setPaymentTime(std::stol(token));

        Print::printPayment(payment);
    }
    file.close();
    std::cout << "=======================\n";
}

const std::vector<std::string>& Terminal::getOperators() const {
    return operators;
}

double Terminal::calculateCommission(const std::string& operatorName, double amount) {
    if (operatorName == "МТС") return amount * 0.02;
    if (operatorName == "Билайн") return amount * 0.015;
    return amount * 0.01;
}


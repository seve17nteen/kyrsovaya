#include <iostream>
#include "Payment.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>

void Payment::setOperatorName(const std::string& name) {
    operatorName = name;
}

void Payment::setPhoneNumber(const std::string& phone) {
    phoneNumber = phone;
}

void Payment::setAmount(double amt) {
    amount = amt;
}

void Payment::setCommission(double comm) {
    commission = comm;
}

void Payment::setPaymentTime(time_t time) {
    paymentTime = time;
}

std::string Payment::getOperatorName() const {
    return operatorName;
}

std::string Payment::getPhoneNumber() const {
    return phoneNumber;
}

double Payment::getAmount() const {
    return amount;
}

double Payment::getCommission() const {
    return commission;
}

time_t Payment::getPaymentTime() const {
    return paymentTime;
}

void Payment::saveToFile(const Payment& payment, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << payment.getOperatorName() << "|"
            << payment.getPhoneNumber() << "|"
            << payment.getAmount() << "|"
            << payment.getCommission() << "|"
            << payment.getPaymentTime() << "\n";
        file.close();
    }
    else {
        std::cerr << "Не удалось открыть файл " << filename << " для записи!\n";
    }
}

Payment Payment::loadFromFile(const std::string& filename) {
    Payment payment;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;

            if (std::getline(iss, token, '|')) payment.setOperatorName(token);
            if (std::getline(iss, token, '|')) payment.setPhoneNumber(token);
            if (std::getline(iss, token, '|')) payment.setAmount(std::stod(token));
            if (std::getline(iss, token, '|')) payment.setCommission(std::stod(token));
            if (std::getline(iss, token, '|')) payment.setPaymentTime(std::stol(token));
        }
        file.close();
    }
    return payment;
}
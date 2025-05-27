#include "Print.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <locale>

void Print::printOperators(const std::vector<std::string>& operators) {
    std::cout << "\n��������� ���������:\n";
    for (size_t i = 0; i < operators.size(); ++i) {
        std::cout << i + 1 << ". " << operators[i] << "\n";
    }
}

void Print::printPayment(const Payment& payment) {
    std::cout << "\n������:\n"
        << "��������: " << payment.getOperatorName() << "\n"
        << "�������: " << payment.getPhoneNumber() << "\n"
        << "�����: " << std::fixed << std::setprecision(2)
        << payment.getAmount() << " ���.\n"
        << "��������: " << payment.getCommission() << " ���.\n";

    time_t payTime = payment.getPaymentTime();
    char timeStr[26];
#ifdef _WIN32
    ctime_s(timeStr, sizeof(timeStr), &payTime);
#else
    ctime_r(&payTime, timeStr);
#endif
    std::cout << "�����: " << timeStr << "-----------------\n";
}

void Print::printReceipt(const Payment& payment) {
    std::cout << "\n=== ��� ===\n"
        << "��������: " << payment.getOperatorName() << "\n"
        << "�������: " << payment.getPhoneNumber() << "\n"
        << "�����: " << std::fixed << std::setprecision(2)
        << payment.getAmount() << " ���.\n"
        << "��������: " << payment.getCommission() << " ���.\n";

    time_t payTime = payment.getPaymentTime();
    char timeStr[26];
#ifdef _WIN32
    ctime_s(timeStr, sizeof(timeStr), &payTime);
#else
    ctime_r(&payTime, timeStr);
#endif
    std::cout << "�����: " << timeStr
        << "===========\n";
}
#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>
#include <string>
#include "Payment.h"

class Terminal {
private:
    std::vector<std::string> operators;
    std::vector<Payment> payments;

public:
    void addOperator(const std::string& name);
    void removeOperator(const std::string& name);
    void processPayment(const Payment& payment);
    void printReceipt(const Payment& payment) const;
    void showOperators() const;
    void showPaymentHistory() const;
    const std::vector<std::string>& getOperators() const;

    static double calculateCommission(const std::string& operatorName, double amount);
};

#endif // TERMINAL_H
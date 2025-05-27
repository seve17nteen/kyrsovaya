#ifndef PRINT_H
#define PRINT_H

#include <vector>
#include <string>
#include "Payment.h"

class Print {
public:
    static void printOperators(const std::vector<std::string>& operators);
    static void printPayment(const Payment& payment);
    static void printReceipt(const Payment& payment);
};

#endif // PRINT_H
#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <ctime>

class Payment {

private:
    std::string operatorName;
    std::string phoneNumber;
    double amount;
    double commission;
    time_t paymentTime;

public:
    void setOperatorName(const std::string& name);
    void setPhoneNumber(const std::string& phone);
    void setAmount(double amt);
    void setCommission(double comm);
    void setPaymentTime(time_t time);

    std::string getOperatorName() const;
    std::string getPhoneNumber() const;
    double getAmount() const;
    double getCommission() const;
    time_t getPaymentTime() const;

    static void saveToFile(const Payment& payment, const std::string& filename);
    static Payment loadFromFile(const std::string& filename);
};

#endif // PAYMENT_H
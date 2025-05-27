#ifndef MENU_H
#define MENU_H

#include <string>

class Menu {
public:
    static int mainMenu();
    static int paymentMenu();
    static int operatorMenu();
    static std::string inputPhoneNumber();
    static double inputAmount();
    static double acceptCash(double requiredAmount);
};

#endif // MENU_H
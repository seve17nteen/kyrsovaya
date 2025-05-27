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
};

#endif // MENU_H
#include <iomanip>
#include <iostream>
#include <cmath>
#include <currency_detail/currency_detail.h>
#include <util/input_output_utils.h>
#include <string>
#include <vector>

void printWelcome() {
    std::cout << "#**********************************************************************************#\n";
    std::cout << "+----------------------------------------------------------------------------------+\n";
    std::cout << "|                                    WELCOME TO                                    |\n";
    std::cout << "|                                     CURRCALC                                     |\n";
    std::cout << "+----------------------------------------------------------------------------------+\n";
    std::cout << "#**********************************************************************************#\n";
    std::cout << '\n';
    std::cout << "Welcome to CurrCalc!\n";
    std::cout << "This program converts a specified amount of money from one currency to another.\n";
    std::cout << "Have fun!\n";
    std::cout << '\n';
}

int getCurrencySelection(bool isInitialCurrencySelection, std::vector<std::string> currencies) {
    if(isInitialCurrencySelection){
        std::cout << "Please select an initial currency, the currency from which you want to convert the amount: \n";
    } else {
        std::cout << "Please select a target currency, the currency to which you want to convert the amount: \n";
    }

    int selection{};

    printCurrencies(currencies);

    bool selectionIsValid{false};
    do{
        std::cout << "Please select a currency by typing in its number from the list.\n";
        std::cout << "Only a number that is on the list my be selected and decimal numbers will be truncated!\n";
        std::cin >> selection;

        selectionIsValid = (!std::cin.fail() && selection >= 1 && selection <= currencies.size()) ? true : false; 
    }while(!selectionIsValid);

    std::cout << "You have selected: " << currencies[selection-1] << '\n';

    return selection;
}

void printCurrencies(std::vector<std::string> currencies) {
    for(int i = 0; i < currencies.size(); i++) {
        std::cout << (i + 1) << ". " << currencies[i] << '\n';
    }
}

double getConversionAmount(){
    double amount{};

    bool inputIsValid{false};
    do{
        std::cout << "Please type in the amount you would like to convert.\n";
        std::cout << "Only positive decimal numbers will be accepted and whole numbers will be converted to decimal numbers.!\n";
        std::cout << "Also, note that all inputs will be rounded to five digits after the decimal point!\n";
        std::cin >> amount;

        inputIsValid = (!std::cin.fail() && amount >= 0) ? true : false; 
    }while(!inputIsValid);

    return std::round(amount * 100000.0) / 100000.0; // Rounding amount to 5 decimal points
}

void printResult(CurrencyDetail currencyDetail, std::string targetCurrency, double initalAmount, double convertedAmount) {
    std::setprecision(5);
    std::cout << "Converted " << initalAmount << " " << currencyDetail.getName() << " to " << convertedAmount << " " << targetCurrency << '\n';
}

void printFarewell() {
    std::cout << "#**********************************************************************************#\n";
    std::cout << "+----------------------------------------------------------------------------------+\n";
    std::cout << "|                                     GOODBYE!                                     |\n";
    std::cout << "|                                 HAVE A GOOD ONE!                                 |\n";
    std::cout << "+----------------------------------------------------------------------------------+\n";
    std::cout << "#**********************************************************************************#\n";
}
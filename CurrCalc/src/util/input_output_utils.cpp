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

int getCurrencySelection(std::vector<std::string> currencies, int initialCurrencyIndex) {
    if(initialCurrencyIndex < 0){
        std::cout << "Please select an initial currency, the currency from which you want to convert the amount: \n";
    } else {
        currencies.erase(currencies.begin() + initialCurrencyIndex); // We don't want the user to pick the initial currency again
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

    selection--; // We displayed the currencies starting with index 1, not 0.

    std::cout << "You have selected: " << currencies[selection] << '\n';

    return selection;
}

void printCurrencies(std::vector<std::string> currencies) {
    for(int i = 0; i < currencies.size(); i++) {
        std::cout << (i + 1) << ". " << currencies[i] << "   ";
        if((i+1) % 10 == 0){
            std::cout << std::endl;
        }
    }
    std::cout << std::endl; // Just to add some space
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

    std::cout << std::endl; // Just to add some space

    return std::round(amount * 100000.0) / 100000.0; // Rounding amount to 5 decimal points
}

void printResult(double conversionAmount, std::string initialCurrency, double convertedAmount, std::string targetCurrency) {
    std::cout << std::fixed;
    std::setprecision(5);
    std::cout << "Converted " << conversionAmount << " " << initialCurrency << " to " << convertedAmount << " " << targetCurrency << '\n';
    std::cout << "1.00000 " << initialCurrency << " is equal to " << (conversionAmount / convertedAmount) << " " << targetCurrency << '\n';
}

void printFarewell() {
    std::cout << "#**********************************************************************************#\n";
    std::cout << "+----------------------------------------------------------------------------------+\n";
    std::cout << "|                                     GOODBYE!                                     |\n";
    std::cout << "|                                 HAVE A GOOD ONE!                                 |\n";
    std::cout << "+----------------------------------------------------------------------------------+\n";
    std::cout << "#**********************************************************************************#\n";
}
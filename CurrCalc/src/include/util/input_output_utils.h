#ifndef INPUT_OUTPUT_UTILS_H
#define INPUT_OUTPUT_UTILS_H

#include <currency_detail/currency_detail.h>
#include <string>
#include <vector>

void printWelcome();

int getCurrencySelection(bool isInitialCurrencySelection, std::vector<std::string> currencies);

void printCurrencies(std::vector<std::string> currencies);

double getConversionAmount();

void printResult(CurrencyDetail currencyDetail, std::string targetCurrency, double initalAmount, double convertedAmount);

void printFarewell();

#endif
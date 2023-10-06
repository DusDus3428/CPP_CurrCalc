#ifndef INPUT_OUTPUT_UTILS_H
#define INPUT_OUTPUT_UTILS_H

#include <currency_detail/currency_detail.h>
#include <string>
#include <vector>

void printWelcome();

int getCurrencySelection(std::vector<std::string> currencies, int initialCurrencyIndex = -1);

void printCurrencies(std::vector<std::string> currencies);

double getConversionAmount();

void printResult(double conversionAmount, std::string initialCurrency, double convertedAmount, std::string targetCurrency);

void printFarewell();

#endif
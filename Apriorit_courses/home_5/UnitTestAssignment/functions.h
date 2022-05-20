#pragma once
// unit_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <algorithm>
#include <iostream>
size_t GetProductsAmount(std::vector<int> prices, int amountOfMoney)
{
    std::sort(prices.begin(), prices.end());

    int sum = 0;
    for (size_t i = 0; i < prices.size(); ++i)
    {
        sum += prices[i];
        if (sum > amountOfMoney)
        {
            return i;
        }
    }

    return prices.size();
}
bool IsLeapYear(unsigned int year) {
    // leap year if perfectly divisible by 400
    if (year % 400 == 0) {
        return true;
    }
    // not a leap year if divisible by 100
    // but not divisible by 400
    else if (year % 100 == 0) {
        return false;
    }
    // leap year if not divisible by 100
    // but divisible by 4
    else if (year % 4 == 0) {
        return true;
    }
    // all other years are not leap years
    else {
        return false;
    }
}

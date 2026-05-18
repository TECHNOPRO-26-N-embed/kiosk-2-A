#include <stdio.h>

double change_calculator(double price, double payment) {
    if (payment < price) {
        return -1;
    }
    return payment - price;
}
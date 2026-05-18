#include <stdio.h>

int change_calculator(int price, int payment) {
    if (payment < price) {
        return -1;
    }
    return payment - price;
}
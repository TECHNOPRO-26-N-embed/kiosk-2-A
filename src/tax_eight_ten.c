#include <stdio.h>

double eight_or_ten(int shouhin_number){
    if (shouhin_number >= 1 && shouhin_number <= 7) {
        return 0.08;
    } else if (shouhin_number >= 8 && shouhin_number <= 10) {
        return 0.10;

    } else {
        return -1;
    }
}
#include <stdio.h>
#include "tax_eight_ten.c"
#include "change_calculator.c"
int main(void) {
    int choice;
    while(1) {
        printf("===Quick Self===\n");
        printf("メインメニュー\n");
        printf("1. 商品カテゴリ\n");
        printf("2. 店員を呼び出す\n");
        //printf("3. メインメニューに戻る\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            while(1){
                double kikuchi_kara_number = 1836;
                double pay;
                printf("How much did you pay?:");
                scanf("%lf", &pay);
                printf("change:%.2lfyen\n", change_calculator(kikuchi_kara_number, pay));
                if (pay >= kikuchi_kara_number) {
                    break;
                }
                printf("Not enough money.\n");
            }
        } else if (choice == 2) {
            return 0;
        }
        else {
            printf("適切な番号を入力してください\n");
        }
    }
    return 0;

}
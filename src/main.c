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
        printf("6.お釣り計算\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            break;
        } else if (choice == 2) {
            return 0;
        } else if(choice == 6) {
            int price, payment;
            printf("総合金額(from kikuchi): ");
            scanf("%d", &price);
            printf("支払金額: ");
            scanf("%d", &payment);
            int change = change_calculator(price, payment);
            if (change == -1) {
                printf("支払金額が足りないんです。\n");
            } else {
                printf("お釣り: %d\n", change);
            }
        }
        else {
            printf("適切な番号を入力してください\n");
        }
    }
    return 0;

}
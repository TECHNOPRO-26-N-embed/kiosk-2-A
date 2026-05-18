#include <stdio.h>

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
            printf("お買い上げありがとうございます！\n");
            printf("*********************************\n");
            printf("購入した商品\n");
            printf("ぼんじり    200円\n");
            printf("*********************************\n");
            break;
        } else if (choice == 2) {
            return 0;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;

}
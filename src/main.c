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
            while (1)
            {
            printf("レシートを発行しますか?\n");
            printf("1. はい 2. いいえ\n");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("レシートを発行します。\n");
                printf("********************************\n");
                printf("  ぼんじり  200円\n");
                printf("  もも  150円\n");
                printf("合計 350円\n");
                printf("********************************\n");
                printf("ありがとうございました！\n");
            } else if (choice == 2) {
                printf("ありがとうございました！\n");
            } else {
                printf("数値を入力してください\n");
            }
            break;
            }
            
        } else if (choice == 2) {
            return 0;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;

}
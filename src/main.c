#include <stdio.h>

int main(void) {
    int choice;
    while(1) {
        printf("===Quick Self===\n");
        printf("メインメニュー\n");
        printf("1. 商品カテゴリ\n");
        printf("2. 店員を呼び出す\n");
        //printf("3. メインメニューに戻る\n");
        printf("4. 商品検索\n");
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
            break;
        } else if (choice == 2) {
            return 0;
        } else if (choice ==4){
            char str[] = "1,2,3,4,5,6,7,8,9,10";//実際は数字ではなく商品名
            char* first_space;
            char*last_space;
            first_space = strchr(str ,' ');
            printf("商品を検索します。\n");
            printf("%s\n ", first_space);
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;

}
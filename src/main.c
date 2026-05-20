#include <stdio.h>
#include <string.h>
#include "change_calculator.c"
#include "tax_eight_ten.c"

int main(void) {
    int choice;
    while(1) {
        //イの担当
        printf("===Quick Self===\n");
        printf("メインメニュー\n");
        printf("1. 商品カテゴリ\n");
        printf("2. 店員を呼び出す\n");
        printf("3. 従業員モード(強制終了)\n");
        printf("4. 商品検索\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        //菊池の担当
        if (choice == 1) {
            printf("商品カテゴリを選びました\n");
            printf("1. ぼんじり\n");
            printf("2. もも\n");
            printf("3. つくね\n");
            printf("4. かわ\n");
            printf("5. せせり\n");
            printf("6. 砂肝\n");
            printf("7. なんこつ\n");
            printf("8. ささみ\n");
            printf("9. ねぎま\n");
            printf("10. つなぎ\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            //イの担当
            int go_menu = 0;
            while(1){
                double kikuchi_kara_number = 1836;
                double pay;
                char buf[32];
                printf("お支払い金額を入力してください (数字 or mでメニュー):");
                if (scanf("%lf", &pay) == 1) {
                    printf("お釣り: %.2lf円\n", change_calculator(kikuchi_kara_number, pay));
                    if (pay >= kikuchi_kara_number) {
                        break;
                    }
                    printf("お金が足りません。\n");
                } else {
                    scanf("%31s", buf);
                    if (strcmp(buf, "m") == 0 || strcmp(buf, "M") == 0) {
                        go_menu = 1;
                        break;
                    } else {
                        printf("数値またはmを入力してください。\n");
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) {}
                    }
                }
            }
            if (go_menu) continue;
            //山下の担当
            while (1){
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
                    break;
                } else if (choice == 2) {
                    printf("ありがとうございました！\n");
                    break;
                } else {
                    printf("数値を入力してください\n");
                    continue;
                }
            }
        } else if (choice == 2) {
            return 0;
        }else if (choice == 3) {
            printf("システムを終了します。\n");
            return 0;
        }
        //飯田の担当 
        else if (choice ==4){
            char str[] = "1,2,3,4,5,6,7,8,9,10";//実際は数字ではなく商品名
            char* first_space;
            char*last_space;
            first_space = strchr(str ,' ');
            printf("商品を検索します。\n");
            printf("%s\n , first_space");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;

}
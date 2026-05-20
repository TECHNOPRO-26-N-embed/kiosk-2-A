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
            typedef struct {
                int id;
                char name[32];
                int price;
                char category[16];
                int stock;
                int tax; // 8 or 10
            } Product;
            Product products[10] = {
                {1, "コーラ", 160, "飲料", 35, 8},
                {2, "お茶", 120, "飲料", 40, 8},
                {3, "ミネラルウォーター", 100, "飲料", 50, 8},
                {4, "サンドイッチ", 350, "軽食", 15, 8},
                {5, "おにぎり", 140, "軽食", 25, 8},
                {6, "カップラーメン", 220, "軽食", 30, 8},
                {7, "ポテトチップ", 180, "軽食", 20, 8},
                {8, "ティッシュ", 300, "日用品", 18, 10},
                {9, "トイレットペーパー", 250, "日用品", 22, 10},
                {10, "米", 450, "日用品", 12, 10}
            };
            int category_choice;
            int done = 0;
            int cart[10] = {0};
            while (!done) {
                printf("カテゴリを選択してください\n");
                printf("1. 飲料\n2. 軽食\n3. 日用品\n4. 完了\n");
                printf("番号を入力: ");
                scanf("%d", &category_choice);
                if (category_choice == 4) break;
                printf("商品リスト:\n");
                for (int i = 0; i < 10; i++) {
                    if ((category_choice == 1 && strcmp(products[i].category, "飲料") == 0) ||
                        (category_choice == 2 && strcmp(products[i].category, "軽食") == 0) ||
                        (category_choice == 3 && strcmp(products[i].category, "日用品") == 0)) {
                        printf("%d. %s %d円 (在庫:%d 税:%d%%)\n", products[i].id, products[i].name, products[i].price, products[i].stock, products[i].tax);
                    }
                }
                printf("商品番号を選択 (0で戻る): ");
                int prod_choice, qty;
                scanf("%d", &prod_choice);
                if (prod_choice == 0) continue;
                if (prod_choice < 1 || prod_choice > 10) {
                    printf("無効な商品番号です\n");
                    continue;
                }
                printf("数量を入力: ");
                scanf("%d", &qty);
                if (qty < 1 || qty > products[prod_choice-1].stock) {
                    printf("在庫不足または無効な数量\n");
                    continue;
                }
                cart[prod_choice-1] += qty;
                printf("カートに追加しました: %s x%d\n", products[prod_choice-1].name, qty);
            }
            double total = 0;
            for (int i = 0; i < 10; i++) {
                if (cart[i] > 0) {
                    double item_total = products[i].price * cart[i];
                    item_total *= (1 + products[i].tax / 100.0);
                    total += item_total;
                }
            }
            double kikuchi_kara_number = total;
            printf("\n合計金額(税金含む): %.0lf円\n", kikuchi_kara_number);
            int go_menu = 0;
            while(1){
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
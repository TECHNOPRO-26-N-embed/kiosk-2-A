#include <stdio.h>
#include <string.h>
#include "change_calculator.c"
#include "tax_eight_ten.c"

#define PRODUCT_COUNT 10
#define MAX_CART_ITEMS 10

typedef struct {
    int number;
    const char *name;
    int price;
    int category;
    int stock;
} Product;

typedef struct {
    int productIndex;
    int quantity;
} CartItem;

static Product products[PRODUCT_COUNT] = {
    {1, "コーラ", 160, 1, 35},
    {2, "お茶", 120, 1, 40},
    {3, "ミネラルウォーター", 100, 1, 50},
    {4, "サンドイッチ", 350, 2, 15},
    {5, "おにぎり", 140, 2, 25},
    {6, "カップラーメン", 220, 2, 30},
    {7, "ポテトチップ", 180, 2, 20},
    {8, "ティッシュ", 300, 3, 18},
    {9, "歯ブラシ", 250, 3, 22},
    {10, "洗剤", 450, 3, 12}
};

static const char *categoryNames[] = {"", "飲み物", "食べ物", "一用品"};

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
            CartItem cart[MAX_CART_ITEMS];
            int cartCount = 0;
            int addMore = 1;
            int i;

            for (i = 0; i < MAX_CART_ITEMS; i++) {
                cart[i].productIndex = -1;
                cart[i].quantity = 0;
            }

            while (addMore) {
                int categoryChoice;
                int productNumber;
                int quantity;
                int productIndex = -1;
                int foundCategoryProduct = 0;

                printf("\n商品カテゴリを選択してください\n");
                printf("1. 飲み物\n");
                printf("2. 食べ物\n");
                printf("3. 一用品\n");
                printf("Enter category number: ");
                if (scanf("%d", &categoryChoice) != 1) {
                    printf("数値を入力してください。\n");
                    while (getchar() != '\n') {}
                    continue;
                }

                if (categoryChoice < 1 || categoryChoice > 3) {
                    printf("カテゴリ番号が不正です。\n");
                    continue;
                }

                printf("\n[%s] の商品一覧\n", categoryNames[categoryChoice]);
                for (i = 0; i < PRODUCT_COUNT; i++) {
                    if (products[i].category == categoryChoice) {
                        printf("%d. %s (%d円 / 在庫:%d)\n",
                               products[i].number,
                               products[i].name,
                               products[i].price,
                               products[i].stock);
                        foundCategoryProduct = 1;
                    }
                }

                if (!foundCategoryProduct) {
                    printf("このカテゴリには商品がありません。\n");
                    continue;
                }

                printf("商品番号を入力してください: ");
                if (scanf("%d", &productNumber) != 1) {
                    printf("数値を入力してください。\n");
                    while (getchar() != '\n') {}
                    continue;
                }

                printf("数量を入力してください(1以上): ");
                if (scanf("%d", &quantity) != 1) {
                    printf("数値を入力してください。\n");
                    while (getchar() != '\n') {}
                    continue;
                }

                if (quantity < 1) {
                    printf("数量は1以上の整数を入力してください。\n");
                    continue;
                }

                for (i = 0; i < PRODUCT_COUNT; i++) {
                    if (products[i].number == productNumber && products[i].category == categoryChoice) {
                        productIndex = i;
                        break;
                    }
                }

                if (productIndex == -1) {
                    printf("商品番号が不正です。\n");
                    continue;
                }

                if (quantity > products[productIndex].stock) {
                    printf("在庫不足です。(現在在庫:%d)\n", products[productIndex].stock);
                    continue;
                }

                for (i = 0; i < cartCount; i++) {
                    if (cart[i].productIndex == productIndex) {
                        cart[i].quantity += quantity;
                        break;
                    }
                }

                if (i == cartCount) {
                    if (cartCount >= MAX_CART_ITEMS) {
                        printf("購入リストが上限です。\n");
                        break;
                    }
                    cart[cartCount].productIndex = productIndex;
                    cart[cartCount].quantity = quantity;
                    cartCount++;
                }

                products[productIndex].stock -= quantity;
                printf("購入リストに追加しました: %s x %d\n", products[productIndex].name, quantity);

                printf("追加購入しますか? (1:はい 2:いいえ): ");
                if (scanf("%d", &choice) != 1) {
                    printf("数値を入力してください。\n");
                    while (getchar() != '\n') {}
                    addMore = 0;
                } else if (choice == 1) {
                    addMore = 1;
                } else {
                    addMore = 0;
                }
            }

            if (cartCount == 0) {
                printf("購入商品がありません。メインメニューに戻ります。\n");
                continue;
            }

            {
                double subTotal = 0;
                double taxTotal = 0;
                double grandTotal;
                double pay;

                printf("\n=== 会計処理 ===\n");
                for (i = 0; i < cartCount; i++) {
                    Product p = products[cart[i].productIndex];
                    double lineSubTotal = p.price * cart[i].quantity;
                    double taxRate = eight_or_ten(p.number);
                    double lineTax = lineSubTotal * taxRate;

                    subTotal += lineSubTotal;
                    taxTotal += lineTax;

                    printf("%s x %d = %.0f円 (税率%.0f%%)\n",
                           p.name,
                           cart[i].quantity,
                           lineSubTotal,
                           taxRate * 100);
                }

                grandTotal = subTotal + taxTotal;
                printf("小計: %.0f円\n", subTotal);
                printf("税額: %.0f円\n", taxTotal);
                printf("合計: %.0f円\n", grandTotal);

                while (1) {
                    printf("お支払い金額を入力してください: ");
                    if (scanf("%lf", &pay) != 1) {
                        printf("数値を入力してください。\n");
                        while (getchar() != '\n') {}
                        continue;
                    }
                    if (change_calculator(grandTotal, pay) < 0) {
                        printf("入金額が不足しています。\n");
                        continue;
                    }
                    printf("おつり: %.2f円\n", change_calculator(grandTotal, pay));
                    break;
                }
            }
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
        } else if (choice == 4) {
            return 0;
        }else if (choice == 5) {
            printf("システムを終了します。\n");
            return 0;
        }
        //飯田の担当 
        else if (choice == 6){
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
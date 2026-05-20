#include <stdio.h>
#include <string.h>
#include "change_calculator.c"
#include "tax_eight_ten.c"

struct StaffCall {
    int terminalid;
    int accountingid;
    char reason[50];
};

void callStaff(struct StaffCall call);

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
            while (1){
                printf("レシートを発行しますか?\n");
                printf("1. はい 2. いいえ\n");
                scanf("%d", &choice);
                if (choice == 1) {
                    printf("レシートを発行します。\n");
                    display_receipt(products, cart, cartCount);
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
            struct StaffCall call;

            printf("端末番号を入力してください: ");
            scanf("%d", &call.terminalid);

            printf("会計番号を入力してください: ");
            scanf("%d", &call.accountingid);

            printf("理由を入力してください: ");
            scanf("%s", call.reason);

            callStaff(call);

            printf("店員を呼び出しています。\n");
            return 0;
        }else if (choice == 5) {
            printf("システムを終了します。\n");
            return 0;
        }

        //飯田の担当 
        else if (choice ==4){
                typedef struct {
                    int id;
                    char name[32];
                    int price;
                    char category[16];
                    int stock;
                    int tax;
                } Product;
                Product products[] = {
                    {1, "コーラ", 160, "飲み物", 35, 8},
                    {2, "お茶", 120, "飲み物", 40, 8},
                    {3, "ミネラルウォーター", 100, "飲み物", 50, 8},
                    {4, "サンドイッチ", 350, "食べ物", 15, 8},
                    {5, "おにぎり", 140, "食べ物", 25, 8},
                    {6, "カップラーメン", 220, "食べ物", 30, 8},
                    {7, "ポテトチップ", 180, "食べ物", 20, 8},
                    {8, "ティッシュ", 300, "日用品", 18, 10},
                    {9, "歯ブラシ", 250, "日用品", 22, 10},
                    {10, "洗剤", 450, "日用品", 12, 10}
                };
                int product_count = sizeof(products)/sizeof(products[0]);

                char search[32];
                int return_to_main_menu = 0;
                while (1) {
                    printf("商品名を入力してください（0でキャンセル）: ");
                    scanf("%s", search);
                    if (strcmp(search, "0") == 0) {
                        printf("キャンセルしてメインメニューに戻ります。\n");
                        return_to_main_menu = 1;
                        break;
                    }

                    // 部分一致検索
                    char normalized_search[64];
                    normalize_for_search(search, normalized_search, sizeof(normalized_search));
                    int found_indexes[10];
                    int found_count = 0;
                    for (int i = 0; i < product_count; i++) {
                        char normalized_name[64];
                        normalize_for_search(products[i].name, normalized_name, sizeof(normalized_name));
                        if (strstr(normalized_name, normalized_search) != NULL) {
                            found_indexes[found_count++] = i;
                        }
                    }

                    if (found_count == 0) {
                        printf("該当する商品がありません。\n");
                        if (strstr(search, "-") != NULL || strstr(search, "－") != NULL || strstr(search, "ー") != NULL) {
                            printf("半角全角が間違っています。\n");
                        }
                        continue;
                    }

                    while (1) {
                        printf("候補商品:\n");
                        for (int i = 0; i < found_count; i++) {
                            int idx = found_indexes[i];
                            int tax_included = products[idx].price + (products[idx].price * products[idx].tax / 100);
                            printf("%d. %s | %s | 税込%d円\n",
                                i+1, products[idx].name, products[idx].category, tax_included);
                        }

                        int select = 0;
                        printf("商品番号を選択してください（0でキャンセル / -1で商品名入力に戻る）: ");
                        scanf("%d", &select);
                        if (select == 0) {
                            printf("キャンセルしてメインメニューに戻ります。\n");
                            return_to_main_menu = 1;
                            break;
                        }
                        if (select == -1) {
                            printf("商品名入力に戻ります。\n");
                            break;
                        }
                        if (select < 1 || select > found_count) {
                            printf("無効な選択です。\n");
                            continue;
                        }

                        int selected_idx = found_indexes[select-1];
                        if (products[selected_idx].stock == 0) {
                            printf("品切れしております。\n");
                            continue;
                        }

                        while (1) {
                            int quantity = 0;
                            printf("数量を入力してください（0でキャンセル / -1で商品選択に戻る）: ");
                            scanf("%d", &quantity);
                            if (quantity == 0) {
                                printf("キャンセルしてメインメニューに戻ります。\n");
                                return_to_main_menu = 1;
                                break;
                            }
                            if (quantity == -1) {
                                printf("商品選択に戻ります。\n");
                                break;
                            }
                            if (quantity < 0) {
                                printf("数量は1以上を入力してください。\n");
                                continue;
                            }
                            if (products[selected_idx].stock < quantity) {
                                printf("残り数量は%d個です。\n", products[selected_idx].stock);
                                continue;
                            }

                            products[selected_idx].stock -= quantity;
                            printf("カートに追加しました: %s x%d\n", products[selected_idx].name, quantity);

                            while (1) {
                                int cancel_after_add = 0;
                                printf("追加を確定しますか？（1: 確定 / 2: この商品をキャンセル / 3: 数量入力に戻る）: ");
                                scanf("%d", &cancel_after_add);
                                if (cancel_after_add == 1) {
                                    printf("商品追加を確定しました。\n");
                                    return_to_main_menu = 1;
                                    break;
                                }
                                if (cancel_after_add == 2) {
                                    products[selected_idx].stock += quantity;
                                    printf("商品追加をキャンセルしました。メインメニューに戻ります。\n");
                                    return_to_main_menu = 1;
                                    break;
                                }
                                if (cancel_after_add == 3) {
                                    products[selected_idx].stock += quantity;
                                    printf("数量入力に戻ります。\n");
                                    break;
                                }
                                printf("無効な選択です。\n");
                            }

                            if (return_to_main_menu) {
                                break;
                            }
                        }

                        if (return_to_main_menu) {
                            break;
                        }
                    }

                    if (return_to_main_menu) {
                        break;
                    }
                }
        }
        else {
            printf("Invalid choice. Please try again.\n");
            printf("%s\n , first_space");

            break;

        }
    
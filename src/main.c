#include <stdio.h>
#include <string.h>
#include "change_calculator.c"
#include "tax_eight_ten.c"

static void normalize_for_search(const char *input, char *output, int output_size) {
    int in_idx = 0;
    int out_idx = 0;
    const unsigned char *p = (const unsigned char *)input;

    while (p[in_idx] != '\0' && out_idx < output_size - 1) {
        if (p[in_idx + 1] != '\0' && p[in_idx + 2] != '\0') {
            // 全角数字 ０-９ -> 半角数字 0-9
            if (p[in_idx] == 0xEF && p[in_idx + 1] == 0xBC && p[in_idx + 2] >= 0x90 && p[in_idx + 2] <= 0x99) {
                output[out_idx++] = '0' + (char)(p[in_idx + 2] - 0x90);
                in_idx += 3;
                continue;
            }
            // 全角英大文字 Ａ-Ｚ -> 半角英大文字 A-Z
            if (p[in_idx] == 0xEF && p[in_idx + 1] == 0xBC && p[in_idx + 2] >= 0xA1 && p[in_idx + 2] <= 0xBA) {
                output[out_idx++] = 'A' + (char)(p[in_idx + 2] - 0xA1);
                in_idx += 3;
                continue;
            }
            // 全角英小文字 ａ-ｚ -> 半角英小文字 a-z
            if (p[in_idx] == 0xEF && p[in_idx + 1] == 0xBD && p[in_idx + 2] >= 0x81 && p[in_idx + 2] <= 0x9A) {
                output[out_idx++] = 'a' + (char)(p[in_idx + 2] - 0x81);
                in_idx += 3;
                continue;
            }
            // 全角ハイフン(－)と半角長音(ｰ)は長音(ー)へ統一
            if ((p[in_idx] == 0xEF && p[in_idx + 1] == 0xBC && p[in_idx + 2] == 0x8D) ||
                (p[in_idx] == 0xEF && p[in_idx + 1] == 0xBD && p[in_idx + 2] == 0xB0)) {
                if (out_idx + 3 >= output_size) {
                    break;
                }
                output[out_idx++] = (char)0xE3;
                output[out_idx++] = (char)0x83;
                output[out_idx++] = (char)0xBC;
                in_idx += 3;
                continue;
            }
        }

        // 半角ハイフン(-)は長音(ー)へ統一
        if (p[in_idx] == '-') {
            if (out_idx + 3 >= output_size) {
                break;
            }
            output[out_idx++] = (char)0xE3;
            output[out_idx++] = (char)0x83;
            output[out_idx++] = (char)0xBC;
            in_idx++;
            continue;
        }

        output[out_idx++] = (char)p[in_idx++];
    }

    output[out_idx] = '\0';
}

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
        }
    }
    return 0;

}
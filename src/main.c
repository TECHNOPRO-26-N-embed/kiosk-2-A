#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRODUCT_COUNT 10
#define CATEGORY_COUNT 3
#define PAYMENT_METHOD_COUNT 4

typedef struct {
    int id;
    const char *name;
    const char *category;
    int price;
    double tax_rate;
} Product;

static const char *CATEGORIES[CATEGORY_COUNT] = {
    "野菜",
    "果物",
    "飲み物"
};

/* 支払方法は配列管理にしているため、追加が簡単 */
static const char *PAYMENT_METHODS[PAYMENT_METHOD_COUNT] = {
    "現金",
    "クレジットカード",
    "電子マネー",
    "QR決済"
};

static const Product PRODUCTS[PRODUCT_COUNT] = {
    {1, "にんじん", "野菜", 120, 0.08},
    {2, "キャベツ", "野菜", 180, 0.08},
    {3, "トマト", "野菜", 150, 0.08},
    {4, "じゃがいも", "野菜", 100, 0.08},
    {5, "りんご", "果物", 140, 0.08},
    {6, "みかん", "果物", 130, 0.08},
    {7, "バナナ", "果物", 160, 0.08},
    {8, "オレンジ", "果物", 170, 0.10},
    {9, "水", "飲み物", 110, 0.10},
    {10, "お茶", "飲み物", 140, 0.10}
};

double change_calculator(double price, double payment) {
    if (payment < price) {
        return -1;
    }
    return payment - price;
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int get_int_input(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("%d から %d の数値を入力してください。\n", min, max);
        clear_input_buffer();
    }
}

static void get_now_string(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", local);
}

static int append_log_csv(
    const Product *product,
    int quantity,
    int subtotal,
    int tax,
    int total,
    const char *payment_method
) {
    FILE *fp = fopen("data/purchase_log.csv", "a");
    char timestamp[20];

    if (fp == NULL) {
        return 0;
    }

    get_now_string(timestamp, sizeof(timestamp));
    fprintf(
        fp,
        "%s,%d,%s,%s,%d,%.0f%%,%d,%d,%d,%s\n",
        timestamp,
        product->id,
        product->name,
        product->category,
        quantity,
        product->tax_rate * 100,
        subtotal,
        tax,
        total,
        payment_method
    );
    fclose(fp);
    return 1;
}

static void show_categories(void) {
    int i;
    printf("\n=== カテゴリ一覧 ===\n");
    for (i = 0; i < CATEGORY_COUNT; i++) {
        printf("%d. %s\n", i + 1, CATEGORIES[i]);
    }
}

static void show_products_by_category(const char *category) {
    int i;
    printf("\n=== 商品一覧（%s）===\n", category);
    for (i = 0; i < PRODUCT_COUNT; i++) {
        if (strcmp(PRODUCTS[i].category, category) == 0) {
            printf(
                "%d. %s %d円 (税率 %.0f%%)\n",
                PRODUCTS[i].id,
                PRODUCTS[i].name,
                PRODUCTS[i].price,
                PRODUCTS[i].tax_rate * 100
            );
        }
    }
}

static const Product *find_product_by_id(int id) {
    int i;
    for (i = 0; i < PRODUCT_COUNT; i++) {
        if (PRODUCTS[i].id == id) {
            return &PRODUCTS[i];
        }
    }
    return NULL;
}

static void purchase_flow(void) {
    int category_choice;
    int product_id;
    int quantity;
    int payment_choice;
    int subtotal;
    int tax;
    int total;
    double payment;
    const Product *selected;

    show_categories();
    category_choice = get_int_input("カテゴリを選択してください: ", 1, CATEGORY_COUNT);

    show_products_by_category(CATEGORIES[category_choice - 1]);
    product_id = get_int_input("商品番号を選択してください: ", 1, PRODUCT_COUNT);
    selected = find_product_by_id(product_id);

    if (selected == NULL || strcmp(selected->category, CATEGORIES[category_choice - 1]) != 0) {
        printf("選択カテゴリにその商品はありません。最初からやり直してください。\n");
        return;
    }

    quantity = get_int_input("数量を入力してください (1-20): ", 1, 20);

    subtotal = selected->price * quantity;
    tax = (int)(subtotal * selected->tax_rate + 0.5);
    total = subtotal + tax;

    printf("\n=== お会計 ===\n");
    printf("商品: %s\n", selected->name);
    printf("カテゴリ: %s\n", selected->category);
    printf("単価: %d円\n", selected->price);
    printf("数量: %d\n", quantity);
    printf("小計: %d円\n", subtotal);
    printf("税額(%.0f%%): %d円\n", selected->tax_rate * 100, tax);
    printf("合計: %d円\n", total);

    printf("\n=== 支払方法 ===\n");
    for (payment_choice = 0; payment_choice < PAYMENT_METHOD_COUNT; payment_choice++) {
        printf("%d. %s\n", payment_choice + 1, PAYMENT_METHODS[payment_choice]);
    }
    payment_choice = get_int_input("支払方法を選択してください: ", 1, PAYMENT_METHOD_COUNT);

    if (strcmp(PAYMENT_METHODS[payment_choice - 1], "現金") == 0) {
        while (1) {
            printf("支払金額を入力してください: ");
            if (scanf("%lf", &payment) != 1) {
                printf("数値を入力してください。\n");
                clear_input_buffer();
                continue;
            }
            if (payment < total) {
                printf("金額が不足しています。\n");
                continue;
            }
            printf("お釣り: %.0f円\n", change_calculator((double)total, payment));
            break;
        }
    } else {
        printf("%s で支払い処理を実行しました。\n", PAYMENT_METHODS[payment_choice - 1]);
    }

    if (append_log_csv(
            selected,
            quantity,
            subtotal,
            tax,
            total,
            PAYMENT_METHODS[payment_choice - 1])) {
        printf("CSVログを保存しました: data/purchase_log.csv\n");
    } else {
        printf("CSVログの保存に失敗しました。\n");
    }

    printf("ご利用ありがとうございました。\n");
}

struct StaffCall {
    int terminalid;
    int accountingid;
    char reason[50];
};

void callStaff(struct StaffCall call);

int main(void) {
    int choice;

    while (1) {
        printf("\n=== Quick Self ===\n");
        printf("1. 会計を開始する\n");
        printf("2. 店員を呼び出す\n");
        printf("3. 終了\n");

        choice = get_int_input("番号を入力してください: ", 1, 3);

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

            break;
        } 


            purchase_flow();

        } else if (choice == 2) {
            printf("店員を呼び出しました。少々お待ちください。\n");
        } else {
            printf("システムを終了します。\n");

            return 0;
        }

        //飯田の担当 
        else if (choice ==4){
            char str[] = "ぼんじり,もも,つくね,かわ,せせり,砂肝,なんこつ,ささみ,ねぎま,つなぎ";
            char* first_space;
            char*last_space;
            first_space = strchr(str ,' ');
            printf("商品を検索します。\n");


            printf("%s\n , first_space");
        }
        else if(choice ==2){
            

        int main(void) ;{
            struct StaffCall call;
            printf("端末番号を入力してください:");
            scanf("%d", &call.terminalid);
            printf("会計番号を入力してください:");
            scanf("%d", &call.accountingid);
            printf("呼び出し理由を入力してください:");
            scanf("%s", call.reason);
            callStaff(call);
            
        }

        
        
        } else {

            printf("%s\n", first_space);
            break;
     } else {
            printf("Invalid choice. Please try again.\n");
            printf("%s\n , first_space");

            break;

        }
    }



void callStaff(struct StaffCall call) {
            printf("店員を呼び出しました。しばらくお待ちください。\n");
            printf("端末番号: %d\n", call.terminalid);
            printf("会計番号: %d\n", call.accountingid);
            printf("呼び出し理由: %s\n", call.reason);
        }

    return 0;
    }


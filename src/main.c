#include <stdio.h>

int main(void) {
    int choice;
    while(1) {
        printf("===Quick Self===\n");
        printf("Main Menu:\n");
        printf("1. Category\n");
        printf("2. Call the staff\n");
        printf("3. メインメニューに戻る\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            break;
        } else if (choice == 2) {
            return 0;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;

}
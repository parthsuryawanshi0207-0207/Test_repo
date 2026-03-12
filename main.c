#include "train.h"

// ==========================================================
// GLOBAL VARIABLE DEFINITIONS
// These are declared as 'extern' in train.h. 
// This is the only file where they are actually allocated memory.
// ==========================================================
Train trains[MAX_TRAINS];
int trainCount = 0;

Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

float totalRevenue = 0.0;

int main() {
    int choice;

    // loadFromFile(); // To be implemented in file_io.c

    while (1) {
        printf("\n=========================================");
        printf("\n       IIT JODHPUR RAILWAY SYSTEM");
        printf("\n=========================================");
        printf("\n1. USER PORTAL (Search & Book)");
        printf("\n2. ADMIN PORTAL (Manage Trains)");
        printf("\n3. EXIT & SAVE");
        printf("\n=========================================");
        printf("\nEnter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Please enter a valid numerical choice.");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                userMenu(); // Logic in user.c
                break;
            case 2:
                adminMenu(); // Logic in admin.c
                break;
            case 3:
                // saveToFile(); 
                printf("\nExiting. Have a safe journey!\n");
                exit(0);
            default:
                printf("\n[Invalid Selection] Try again.\n");
        }
    }
    return 0;
}

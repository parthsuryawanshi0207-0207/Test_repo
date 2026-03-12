#include "train.h"

// Secure Admin Login
int adminLogin() {
    char username[20], password[20];
    printf("\n--- Admin Authentication ---");
    printf("\nEnter Admin ID: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "iitj123") == 0) {
        printf("\nLogin Successful!\n");
        return 1;
    } else {
        printf("\nInvalid Credentials. Access Denied!\n");
        return 0;
    }
}

// 1. Add Train Details
void addTrain() {
    if (trainCount >= MAX_TRAINS) {
        printf("\nError: Maximum train capacity reached!\n");
        return;
    }

    Train *newTrain = &trains[trainCount]; 

    printf("\nEnter Train Number: ");
    scanf("%d", &newTrain->trainNo);
    printf("Enter Train Name: ");
    getchar(); 
    fgets(newTrain->name, 50, stdin);
    newTrain->name[strcspn(newTrain->name, "\n")] = 0; 

    printf("Enter Source: ");
    scanf("%s", newTrain->src);
    printf("Enter Destination: ");
    scanf("%s", newTrain->dest);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", newTrain->date);
    printf("Enter Dep. Time (HHMM): ");
    scanf("%d", &newTrain->depTime);
    printf("Enter Arr. Time (HHMM): ");
    scanf("%d", &newTrain->arrTime);

    printf("Enter AC Fare: ");
    scanf("%f", &newTrain->priceAC);
    printf("Enter Sleeper Fare: ");
    scanf("%f", &newTrain->priceSleeper);
    printf("Seats (AC): ");
    scanf("%d", &newTrain->seatsAC);
    printf("Seats (Sleeper): ");
    scanf("%d", &newTrain->seatsSleeper);

    trainCount++;
    printf("\nTrain added successfully!\n");
}

// 2. Edit Train Details (Algorithm: Linear Search & Overwrite)
void editTrain() {
    int tNo, found = 0;
    printf("\nEnter Train Number to edit: ");
    scanf("%d", &tNo);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainNo == tNo) {
            printf("Editing Train: %s\n", trains[i].name);
            printf("Enter New AC Fare: ");
            scanf("%f", &trains[i].priceAC);
            printf("Enter New Sleeper Fare: ");
            scanf("%f", &trains[i].priceSleeper);
            printf("Enter New AC Seats: ");
            scanf("%d", &trains[i].seatsAC);
            printf("Enter New Sleeper Seats: ");
            scanf("%d", &trains[i].seatsSleeper);
            
            printf("\nTrain details updated!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Train not found!\n");
}

// 3. Delete Train (Algorithm: Array Shifting)
void deleteTrain() {
    int tNo, found = 0;
    printf("\nEnter Train Number to delete: ");
    scanf("%d", &tNo);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainNo == tNo) {
            for (int j = i; j < trainCount - 1; j++) {
                trains[j] = trains[j + 1]; // Shifting elements left
            }
            trainCount--;
            printf("\nTrain deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Train not found!\n");
}

// 4. View Statistics (Total Money Earned)
void displayStats() {
    printf("\n--- System Statistics ---");
    printf("\nTotal Trains Managed: %d", trainCount);
    // Note: totalRevenue variable would be updated by booking.c logic
    printf("\nTotal Revenue (Dashboard): $%.2f", totalRevenue); 
    printf("\n-------------------------\n");
}

void adminMenu() {
    if (!adminLogin()) return;

    int choice;
    while (1) {
        printf("\n=== Admin Dashboard ===");
        printf("\n1. Add New Train");
        printf("\n2. Edit Train Details");
        printf("\n3. Delete Train");
        printf("\n4. View System Stats");
        printf("\n5. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTrain(); break;
            case 2: editTrain(); break;
            case 3: deleteTrain(); break;
            case 4: displayStats(); break;
            case 5: return;
            default: printf("Invalid option!\n");
        }
    }
}

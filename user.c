#include "train.h"

// The Two-Hop Pathfinding Logic
void searchConnecting(char* start, char* end, char* travelDate) {
    int found = 0;
    printf("\n--- Searching for Connections ---");

    for (int i = 0; i < trainCount; i++) {
        if (strcmp(trains[i].src, start) == 0 && strcmp(trains[i].date, travelDate) == 0) {
            char hub[50];
            strcpy(hub, trains[i].dest); 

            for (int j = 0; j < trainCount; j++) {
                if (strcmp(trains[j].src, hub) == 0 && strcmp(trains[j].dest, end) == 0 && strcmp(trains[j].date, travelDate) == 0) {
                    
                    if (trains[i].arrTime + 30 < trains[j].depTime) { 
                        printf("\n[CONNECTION FOUND!] via %s", hub);
                        printf("\nLeg 1: Train %d (%s -> %s)", trains[i].trainNo, start, hub);
                        printf("\nLeg 2: Train %d (%s -> %s)", trains[j].trainNo, hub, end);
                        printf("\nTotal AC Fare: %.2f", (trains[i].priceAC + trains[j].priceAC));
                        printf("\n----------------------------------");
                        found = 1;
                    }
                }
            }
        }
    }
    if (!found) printf("\nNo connecting routes available.");
}

void userMenu() {
    int choice;
    char s[50], d[50], dt[15];

    while (1) {
        printf("\n=== USER PORTAL ===");
        printf("\n1. Search Trains (Direct & Connecting)");
        printf("\n2. Book a Ticket (Using Train Number)");
        printf("\n3. Cancel a Ticket");
        printf("\n4. Back to Main Menu");
        printf("\nChoice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter Source: "); scanf("%s", s);
                printf("Enter Destination: "); scanf("%s", d);
                printf("Enter Date (DD/MM/YYYY): "); scanf("%s", dt);

                int directFound = 0;
                printf("\n--- Direct Trains ---");
                for (int i = 0; i < trainCount; i++) {
                    if (strcmp(trains[i].src, s) == 0 && strcmp(trains[i].dest, d) == 0 && strcmp(trains[i].date, dt) == 0) {
                        printf("\nTrain No: %d | Name: %s | Dep: %04d", trains[i].trainNo, trains[i].name, trains[i].depTime);
                        directFound = 1;
                    }
                }

                if (!directFound) {
                    searchConnecting(s, d, dt); 
                }
                break;

            case 2:
                // This calls the function in booking.c
                bookTicket(); 
                break;

            case 3:
                // This calls the function in booking.c
                cancelTicket();
                break;

            case 4:
                return;

            default:
                printf("\nInvalid selection.");
        }
    }
}
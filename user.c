#include "train.h"

// The "Two-Hop" Pathfinding Logic
void searchConnecting(char* start, char* end, char* travelDate) {
    int found = 0;
    printf("\n--- Searching for Connections ---");

    for (int i = 0; i < trainCount; i++) {
        // Find trains leaving from Start City
        if (strcmp(trains[i].src, start) == 0 && strcmp(trains[i].date, travelDate) == 0) {
            
            char hub[50];
            strcpy(hub, trains[i].dest); 

            // Search for a train from that Hub to the Destination
            for (int j = 0; j < trainCount; j++) {
                if (strcmp(trains[j].src, hub) == 0 && strcmp(trains[j].dest, end) == 0 && strcmp(trains[j].date, travelDate) == 0) {
                    
                    // Time Validation: Ensure Leg 1 arrives before Leg 2 departs
                    if (trains[i].arrTime + 30 < trains[j].depTime) { 
                        printf("\n[CONNECTION FOUND!] via %s", hub);
                        printf("\nLeg 1: %s -> %s (Train %d)", start, hub, trains[i].trainNo);
                        printf("\nLeg 2: %s -> %s (Train %d)", hub, end, trains[j].trainNo);
                        printf("\nTotal AC Fare: %.2f", (trains[i].priceAC + trains[j].priceAC));
                        printf("\n----------------------------------");
                        found = 1;
                    }
                }
            }
        }
    }
    if (!found) printf("\nNo direct or connecting routes available.");
}

void userMenu() {
    int choice;
    char s[50], d[50], dt[15];

    while (1) {
        printf("\n=== USER MENU ===");
        printf("\n1. Search Train\n2. Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Source: "); scanf("%s", s);
            printf("Destination: "); scanf("%s", d);
            printf("Date (DD/MM/YYYY): "); scanf("%s", dt);

            int directFound = 0;
            for (int i = 0; i < trainCount; i++) {
                if (strcmp(trains[i].src, s) == 0 && strcmp(trains[i].dest, d) == 0 && strcmp(trains[i].date, dt) == 0) {
                    printf("\nDirect Train: %s (%d)", trains[i].name, trains[i].trainNo);
                    directFound = 1;
                }
            }

            if (!directFound) {
                searchConnecting(s, d, dt); // Trigger Algorithm
            }
        } 
        else if (choice == 2) return;
    }
}

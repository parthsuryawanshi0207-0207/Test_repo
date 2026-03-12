#include "train.h"
#include <time.h>

// Helper Function: Generate a Unique PNR
int generatePNR() {
    srand(time(0));
    return rand() % 900000 + 100000; // Generates a 6-digit PNR
}

// Feature: Billing with GST
void generateBill(float baseFare, char* category) {
    float gstRate = (strcmp(category, "AC") == 0) ? 0.12 : 0.05; // 12% for AC, 5% for Sleeper
    float tax = baseFare * gstRate;
    float total = baseFare + tax;

    printf("\n---------- INVOICE ----------");
    printf("\nBase Fare:      INR %.2f", baseFare);
    printf("\nGST (%d%%):      INR %.2f", (int)(gstRate * 100), tax);
    printf("\n-----------------------------");
    printf("\nTOTAL PAYABLE:  INR %.2f", total);
    printf("\n-----------------------------");
    
    totalRevenue += total; // Update Admin Dashboard stats
}

// Feature: Booking and Seat Management
void bookTicket() {
    int tNo, choice;
    printf("\nEnter Train Number to Book: ");
    scanf("%d", &tNo);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainNo == tNo) {
            printf("\nSelect Category:\n1. AC (INR %.2f)\n2. Sleeper (INR %.2f)\nChoice: ", trains[i].priceAC, trains[i].priceSleeper);
            scanf("%d", &choice);

            Booking *newB = &bookings[bookingCount];
            newB->trainNo = tNo;
            newB->pnr = generatePNR();
            newB->status = 1; // 1 = Active

            printf("Enter Passenger Name: ");
            getchar(); // Buffer clear
            fgets(newB->passengerName, 50, stdin);
            newB->passengerName[strcspn(newB->passengerName, "\n")] = 0;

            if (choice == 1) {
                if (trains[i].seatsAC > 0) {
                    strcpy(newB->seatCategory, "AC");
                    newB->totalBill = trains[i].priceAC * 1.12;
                    trains[i].seatsAC--; // Deduct seat
                    generateBill(trains[i].priceAC, "AC");
                } else {
                    printf("\nNo AC seats available!"); return;
                }
            } else {
                if (trains[i].seatsSleeper > 0) {
                    strcpy(newB->seatCategory, "Sleeper");
                    newB->totalBill = trains[i].priceSleeper * 1.05;
                    trains[i].seatsSleeper--; // Deduct seat
                    generateBill(trains[i].priceSleeper, "Sleeper");
                } else {
                    printf("\nNo Sleeper seats available!"); return;
                }
            }

            printf("\nBooking Successful! Your PNR is: %d\n", newB->pnr);
            bookingCount++;
            return;
        }
    }
    printf("\nTrain not found.");
}

// Feature: Cancel Booking
void cancelTicket() {
    int pnrIn, found = 0;
    printf("\nEnter PNR to Cancel: ");
    scanf("%d", &pnrIn);

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].pnr == pnrIn && bookings[i].status == 1) {
            bookings[i].status = 0; // Mark as Cancelled
            
            // Refund Logic: Deduct 20% as cancellation charges
            float refund = bookings[i].totalBill * 0.80;
            printf("\nTicket Cancelled. Refund of INR %.2f processed.", refund);
            
            // Return the seat to the train array
            for (int j = 0; j < trainCount; j++) {
                if (trains[j].trainNo == bookings[i].trainNo) {
                    if (strcmp(bookings[i].seatCategory, "AC") == 0) trains[j].seatsAC++;
                    else trains[j].seatsSleeper++;
                    break;
                }
            }
            found = 1; break;
        }
    }
    if (!found) printf("\nPNR not found or already cancelled.");
}
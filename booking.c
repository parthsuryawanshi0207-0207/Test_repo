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
                    newB->totalBill = trains

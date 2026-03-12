#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAX_TRAINS 50
#define MAX_BOOKINGS 100

// 1. The Train Structure (Core Data)
typedef struct {
    int trainNo;
    char name[50];
    char src[50];
    char dest[50];
    char date[15];
    int depTime;        // Format: HHMM (e.g., 1430 for 2:30 PM)
    int arrTime;        // Format: HHMM
    float priceAC;      
    float priceSleeper; 
    int seatsAC;
    int seatsSleeper;
} Train;

// 2. The Booking Structure (For Transactions)
typedef struct {
    int pnr;
    int trainNo;
    char passengerName[50];
    char seatCategory[10]; // "AC" or "Sleeper"
    float totalBill;       // Includes GST
    int status;            // 1 for Active, 0 for Cancelled
} Booking;

// 3. Global Variables (Shared across all .c files)
// 'extern' tells the compiler these are defined in main.c
extern Train trains[MAX_TRAINS];
extern int trainCount;
extern Booking bookings[MAX_BOOKINGS];
extern int bookingCount;
extern float totalRevenue;

// 4. Function Prototypes (So files can talk to each other)

// Admin functions (admin.c)
void adminMenu();
void addTrain();
void editTrain();
void deleteTrain();

// User/Search functions (user.c)
void userMenu();
void searchDirect();
void searchConnecting(); // The Two-Hop Pathfinding Algorithm

// Booking/Billing functions (booking.c)
void bookTicket();
void cancelTicket();
void generateBill(float baseFare, char* category);

// File functions (file_io.c)
void saveToFile();
void loadFromFile();

#endif

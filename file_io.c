#include "train.h"

// Feature: Save Data to Hard Drive
void saveToFile() {
    FILE *tFile = fopen("trains.dat", "wb");
    FILE *bFile = fopen("bookings.dat", "wb");
    FILE *rFile = fopen("revenue.dat", "wb");

    if (tFile == NULL || bFile == NULL || rFile == NULL) {
        printf("\n[Error] Could not open files for saving!\n");
        return;
    }

    // Write the counts first, then the arrays
    fwrite(&trainCount, sizeof(int), 1, tFile);
    fwrite(trains, sizeof(Train), trainCount, tFile);

    fwrite(&bookingCount, sizeof(int), 1, bFile);
    fwrite(bookings, sizeof(Booking), bookingCount, bFile);

    // Save total revenue
    fwrite(&totalRevenue, sizeof(float), 1, rFile);

    fclose(tFile);
    fclose(bFile);
    fclose(rFile);
    printf("\n[System] All data saved successfully to .dat files.\n");
}

// Feature: Load Data at Startup
void loadFromFile() {
    FILE *tFile = fopen("trains.dat", "rb");
    FILE *bFile = fopen("bookings.dat", "rb");
    FILE *rFile = fopen("revenue.dat", "rb");

    // If files don't exist yet, just return
    if (tFile == NULL) {
        printf("\n[System] No existing train database found. Starting fresh.\n");
        return;
    }

    // Read train data
    fread(&trainCount, sizeof(int), 1, tFile);
    fread(trains, sizeof(Train), trainCount, tFile);

    // Read booking data
    if (bFile != NULL) {
        fread(&bookingCount, sizeof(int), 1, bFile);
        fread(bookings, sizeof(Booking), bookingCount, bFile);
        fclose(bFile);
    }

    // Read revenue
    if (rFile != NULL) {
        fread(&totalRevenue, sizeof(float), 1, rFile);
        fclose(rFile);
    }

    fclose(tFile);
    printf("\n[System] Database loaded: %d trains and %d bookings found.\n", trainCount, bookingCount);
}

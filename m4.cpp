/*
* FILE : m4.cpp
* PROJECT : SENG1000 - Major Assignment #4
* PROGRAMMER : Ayushkumar Bhupatbhai Rakholiya
* FIRST VERSION : 2024-04-1
* DESCRIPTION :
*   This program program used pointer variables to modify parameters.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char source[50];
    char destination[50];
    int fare;
    char airline[50];
} Flight;

Flight flights[100];
int num_flights = 0;

int main() {
    char filename[256];
    FILE* file;
    errno_t err = fopen_s(&file, "flights.txt", "r");
    if (err != 0) {
        printf("Cannot open file: flights.txt\n");
        return 1;
    }

    while (fgets(filename, sizeof(filename), file)) {
        // Remove the newline character from the filename
        filename[strcspn(filename, "\n")] = 0;

        // Skip empty lines
        if (strcmp(filename, "") == 0) {
            continue;
        }

        processFlight(filename, flights, &num_flights);
    }

    fclose(file);

    // Add a blank line before displaying the fare details
    printf("\n");

    displayLeastFareDetails(flights, num_flights);

    return 0;
}

int parseLine(char* line, char* filename, char* source, char* destination, int* fare) {
    char* comma = strchr(line, ',');
    char* dash = strchr(line, '-');

    if (comma == NULL) {
        printf("Error processing file %s line: %s\nMissing comma in %s\n", filename, line, line);
        return -1;
    }
    else if (dash == NULL) {
        printf("Error processing file %s line: %s\nMissing dash in %s\n", filename, line, line);
        return -1;
    }
    else {
        sscanf_s(line, "%49[^-] - %49[^,], %d", source, (unsigned int)sizeof(source), destination, (unsigned int)sizeof(destination), fare);
        return 0;
    }
}

int processFlight(char* filename, Flight* flights, int* num_flights) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        printf("Cannot open file: %s\n", filename);
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) {
            continue;
        }

        Flight flight;
        int status = parseLine(line, filename, flight.source, flight.destination, &flight.fare);
        if (status == 0) {
            strcpy_s(flight.airline, sizeof(flight.airline), filename);
            flights[(*num_flights)++] = flight;
        }
    }

    fclose(file);
    return 0;
}

void displayLeastFareDetails(Flight* flights, int num_flights) {
    int processed[100] = { 0 };

    for (int i = 0; i < num_flights; i++) {
        if (processed[i]) {
            continue;
        }

        Flight min_fare_flight = flights[i];
        for (int j = i + 1; j < num_flights; j++) {
            if (strcmp(flights[i].source, flights[j].source) == 0 && strcmp(flights[i].destination, flights[j].destination) == 0) {
                processed[j] = 1;
                if (flights[j].fare < min_fare_flight.fare) {
                    min_fare_flight = flights[j];
                }
            }
        }
        printf("%s : %s to %s, fare $%d\n", min_fare_flight.airline, min_fare_flight.source, min_fare_flight.destination, min_fare_flight.fare);
    }
}
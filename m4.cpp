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
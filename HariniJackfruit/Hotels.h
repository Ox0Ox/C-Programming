#ifndef HOTELS_H
#define HOTELS_H

#define MAX_PLACES 5
#define MAX_HOTELS_PER_BUDGET 3
#define MAX_BUDGETS 3
#define MAX_HOTEL_NAME_LENGTH 200  // Increased from 60 to 80 to accommodate longer hotel names

// Structure to hold hotels for each place
typedef struct {
    char place[30];
    char budget_hotels[MAX_BUDGETS][MAX_HOTELS_PER_BUDGET][MAX_HOTEL_NAME_LENGTH];
    int hotels_count[MAX_BUDGETS]; // Number of hotels per budget category
} PlaceHotels;

// Hotel arrays for each category
extern const PlaceHotels adventure_hotels[MAX_PLACES];
extern const PlaceHotels relaxation_hotels[MAX_PLACES];
extern const PlaceHotels culture_hotels[MAX_PLACES];

// Function to get hotels for a specific place and category
const PlaceHotels* get_place_hotels(const char* place_name, int category);

// Function to get all hotels for a category
const PlaceHotels* get_category_hotels(int category);

#endif
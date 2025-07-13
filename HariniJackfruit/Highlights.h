#ifndef HIGHLIGHTS_H
#define HIGHLIGHTS_H

#define MAX_PLACES 5
#define MAX_HIGHLIGHTS 4
#define MAX_TEXT_LENGTH 100

// Structure to hold highlights for each destination
typedef struct {
    char place[MAX_TEXT_LENGTH];
    char highlights[MAX_HIGHLIGHTS][MAX_TEXT_LENGTH];
    int num_highlights;
} PlaceHighlights;

// Category highlight arrays
extern const PlaceHighlights adventure_highlights[MAX_PLACES];
extern const PlaceHighlights relaxation_highlights[MAX_PLACES];
extern const PlaceHighlights culture_highlights[MAX_PLACES];

// Function to get highlights for a specific place and category
const PlaceHighlights* get_place_highlights(const char* place_name, int category);

// Function to get all highlights for a category
const PlaceHighlights* get_category_highlights(int category);

#endif
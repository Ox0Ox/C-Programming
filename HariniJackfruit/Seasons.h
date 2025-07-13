#ifndef SEASONS_H
#define SEASONS_H

#define MAX_SEASONAL_PLACES 9
#define MAX_PLACE_NAME 20

// Seasonal destination arrays
extern const char summer_destinations[MAX_SEASONAL_PLACES][MAX_PLACE_NAME];
extern const char winter_destinations[7][MAX_PLACE_NAME];
extern const char spring_destinations[5][MAX_PLACE_NAME];
extern const char autumn_destinations[5][MAX_PLACE_NAME];

// Function to get seasonal destinations
const char (*get_seasonal_destinations(int season, int *count))[MAX_PLACE_NAME];

#endif
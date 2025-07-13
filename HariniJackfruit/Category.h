#ifndef CATEGORY_H
#define CATEGORY_H

#define MAX_DESTINATIONS 5
#define MAX_NAME_LENGTH 20

// Category arrays
extern const char adventure[MAX_DESTINATIONS][MAX_NAME_LENGTH];
extern const char relaxation[MAX_DESTINATIONS][MAX_NAME_LENGTH];
extern const char culture[MAX_DESTINATIONS][MAX_NAME_LENGTH];

// Function to get category array based on choice
const char (*get_category(int choice))[MAX_NAME_LENGTH];

#endif
#ifndef DATERANGES_H
#define DATERANGES_H

// Date structure
typedef struct {
    int month;
    int day;
} Date;

// Season date ranges
typedef struct {
    Date start;
    Date end;
} SeasonRange;

// Season definitions
extern const SeasonRange spring;
extern const SeasonRange summer;
extern const SeasonRange autumn;
extern const SeasonRange winter;

// Function to determine season based on date
int get_season(Date start_date, Date end_date);

// Function to create date from month and day
Date create_date(int month, int day);

// Function to compare dates (returns 1 if date1 >= date2, 0 otherwise)
int compare_dates(Date date1, Date date2);

#endif
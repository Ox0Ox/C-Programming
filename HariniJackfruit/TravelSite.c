#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isspace, isdigit

#include "Budget.h"
#include "Category.h"
#include "DateRanges.h"
#include "Highlights.h"
#include "Hotels.h"
#include "Seasons.h"

// Assuming these constants might be in your headers, adding placeholders if not.
// If they are in your .h files, these definitions here are not strictly needed.
#ifndef MAX_DESTINATIONS
#define MAX_DESTINATIONS 5
#endif
#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 100
#endif
#ifndef MAX_PLACES
#define MAX_PLACES 5 // Assuming same as MAX_DESTINATIONS for consistency in arrays
#endif
#ifndef MAX_HOTELS_PER_BUDGET
#define MAX_HOTELS_PER_BUDGET 3
#endif
#ifndef MAX_BUDGETS
#define MAX_BUDGETS 3
#endif
#ifndef MAX_HOTEL_NAME_LENGTH
#define MAX_HOTEL_NAME_LENGTH 100
#endif
#ifndef MAX_HIGHLIGHTS_PER_PLACE
#define MAX_HIGHLIGHTS_PER_PLACE 4
#endif
#ifndef MAX_SEASONAL_PLACES
#define MAX_SEASONAL_PLACES 9 // As per summer_destinations
#endif
#ifndef MAX_PLACE_NAME
#define MAX_PLACE_NAME MAX_NAME_LENGTH // Assuming place names have consistent max length
#endif


// =============================================================================
// BUDGET IMPLEMENTATION (MODIFIED WITH REALISTIC VALUES)
// =============================================================================
// Realistic budget for one person per day in CHF
// Minimum: 120 CHF, Mid-range: 280 CHF, Luxury: 550 CHF
const BudgetRange one_person_budget = {120, 280, 550}; // Updated values
const double CHF_TO_INR_RATE = 102.92; // Based on recent search

void calculate_budget(int num_people, int budget_result_chf[3], double budget_result_inr[3]) {
    budget_result_chf[0] = one_person_budget.minimum * num_people;
    budget_result_chf[1] = one_person_budget.mid_range * num_people;
    budget_result_chf[2] = one_person_budget.luxury * num_people;

    budget_result_inr[0] = budget_result_chf[0] * CHF_TO_INR_RATE;
    budget_result_inr[1] = budget_result_chf[1] * CHF_TO_INR_RATE;
    budget_result_inr[2] = budget_result_chf[2] * CHF_TO_INR_RATE;
}

// =============================================================================
// CATEGORY IMPLEMENTATION ( 그대로 유지 )
// =============================================================================
const char adventure[MAX_DESTINATIONS][MAX_NAME_LENGTH] = {
    "Interlaken", "Zermatt", "Davos", "Grindelwald", "Andermatt"
};
const char relaxation[MAX_DESTINATIONS][MAX_NAME_LENGTH] = {
    "St. Moritz", "Bad Ragaz", "Lugano", "Geneva", "Lenzerheide"
};
const char culture[MAX_DESTINATIONS][MAX_NAME_LENGTH] = {
    "Lucerne", "Bern", "Geneva", "Zurich", "Appenzell"
};
const char (*get_category(int choice))[MAX_NAME_LENGTH] {
    switch(choice) {
        case 1: return adventure;
        case 2: return relaxation;
        case 3: return culture;
        default: return NULL;
    }
}

// =============================================================================
// DATE RANGES IMPLEMENTATION ( 그대로 유지 )
// =============================================================================
const SeasonRange spring = {{3, 1}, {5, 31}};
const SeasonRange summer = {{6, 1}, {8, 31}};
const SeasonRange autumn = {{9, 1}, {11, 30}};
const SeasonRange winter = {{12, 1}, {2, 28}}; // Assuming non-leap year for simplicity

Date create_date(int month, int day) {
    Date date;
    date.month = month;
    date.day = day;
    return date;
}

int compare_dates(Date date1, Date date2) {
    if (date1.month > date2.month)
        return 1;
    else if (date1.month == date2.month && date1.day >= date2.day)
        return 1;
    return 0;
}

int get_season(Date start_date, Date end_date) {
    // Basic check: if the trip is entirely within a season.
    // More sophisticated logic would handle trips spanning season boundaries differently.

    // Check Spring
    if (compare_dates(start_date, spring.start) && compare_dates(spring.end, end_date))
        return 1; // Spring

    // Check Summer
    if (compare_dates(start_date, summer.start) && compare_dates(summer.end, end_date))
        return 2; // Summer

    // Check Autumn
    if (compare_dates(start_date, autumn.start) && compare_dates(autumn.end, end_date))
        return 3; // Autumn

    // Check Winter (simplified logic from original, with slight adaptation)
    // This logic assumes Feb 28 is the end of winter for simplicity, not handling leap years.
    // Winter: Dec 1 to Feb 28
    Date winter_start_actual = winter.start; // {12, 1}
    Date winter_end_actual = winter.end;     // {2, 28}

    // Case 1: Trip is entirely within Dec (e.g., Dec 5 - Dec 20)
    if (start_date.month == 12 && end_date.month == 12 &&
        compare_dates(start_date, winter_start_actual) && compare_dates(create_date(12, 31), end_date)) {
        return 4; // Winter
    }
    // Case 2: Trip is entirely within Jan or Feb (e.g., Jan 10 - Jan 25, Feb 5 - Feb 20, Jan 20 - Feb 10)
    if ((start_date.month == 1 || start_date.month == 2) &&
        (end_date.month == 1 || end_date.month == 2) &&
        compare_dates(start_date, create_date(1,1)) && compare_dates(winter_end_actual, end_date) &&
        compare_dates(end_date, start_date) ) { // ensure end_date is not before start_date
        return 4; // Winter
    }
    // Case 3: Trip spans Dec to Jan/Feb (e.g., Dec 20 - Jan 10)
    if (start_date.month == 12 && (end_date.month == 1 || end_date.month == 2) &&
        compare_dates(start_date, winter_start_actual) && compare_dates(winter_end_actual, end_date)) {
         // Ensure end date is logically after start date considering year change
        if (end_date.month < start_date.month || // e.g. Dec to Jan/Feb (month numbers decrease)
            (end_date.month == start_date.month && end_date.day >= start_date.day)) { // same month, days check
             return 4; // Winter
        }
    }
    return 0; // Invalid or mixed season based on current simplified logic
}


// =============================================================================
// HIGHLIGHTS IMPLEMENTATION ( 그대로 유지 )
// =============================================================================
const PlaceHighlights adventure_highlights[MAX_PLACES] = {
    {"Interlaken", {"Skydiving", "Paragliding", "Canyoning", "Bungee jumping"}, 4},
    {"Zermatt", {"Mountaineering", "Skiing", "Glacier hiking (Matterhorn)", ""}, 3},
    {"Davos", {"Snowboarding", "Mountain biking", "Hiking trails", ""}, 3},
    {"Grindelwald", {"Via Ferrata", "First Cliff Walk", "Alpine hiking", ""}, 3},
    {"Andermatt", {"Off-piste skiing", "Alpine touring", "Freeriding", ""}, 3}
};
const PlaceHighlights relaxation_highlights[MAX_PLACES] = {
    {"St. Moritz", {"Luxury spas", "Serene lakes", "Gourmet dining", ""}, 3},
    {"Bad Ragaz", {"Thermal spas", "Health retreats", "Calm scenery", ""}, 3},
    {"Lugano", {"Lakeside relaxation", "Mediterranean vibes", "", ""}, 2},
    {"Geneva", {"Lake Geneva", "Wine tours", "Lakeside strolls", "Boat cruises"}, 4},
    {"Lenzerheide", {"Wellness hotels", "Tranquil alpine nature", "", ""}, 2}
};
const PlaceHighlights culture_highlights[MAX_PLACES] = {
    {"Lucerne", {"Chapel Bridge", "Old town", "Music festivals", ""}, 3},
    {"Bern", {"UNESCO old town", "Museums", "Zytglogge", ""}, 3},
    {"Geneva", {"United Nations", "Museums", "International culture", ""}, 3},
    {"Zurich", {"Art galleries", "Opera house", "Historic sites", ""}, 3},
    {"Appenzell", {"Folk traditions", "Cheese culture", "Colorful architecture", ""}, 3}
};
const PlaceHighlights* get_place_highlights(const char* place_name, int category) {
    const PlaceHighlights* highlights_array;
    switch(category) {
        case 1: highlights_array = adventure_highlights; break;
        case 2: highlights_array = relaxation_highlights; break;
        case 3: highlights_array = culture_highlights; break;
        default: return NULL;
    }
    for(int i = 0; i < MAX_PLACES; i++) {
        if(strcmp(highlights_array[i].place, place_name) == 0) {
            return &highlights_array[i];
        }
    }
    return NULL;
}
const PlaceHighlights* get_category_highlights(int category) {
    switch(category) {
        case 1: return adventure_highlights;
        case 2: return relaxation_highlights;
        case 3: return culture_highlights;
        default: return NULL;
    }
}

// =============================================================================
// HOTELS IMPLEMENTATION ( 그대로 유지 )
// =============================================================================
const PlaceHotels adventure_hotels[MAX_PLACES] = {
    {"Interlaken", {{"Hotel Weisses Kreuz", "Alplodge", "Hotel Crystal"}, {"Hotel Bernerhof", "Hotel Krebs", "Cityhotel Oberland"}, {"Hotel Royal St. Georges Interlaken MGallery", "Metropole Swiss Quality Hotel", ""}}, {3, 3, 2}},
    {"Zermatt", {{"Hotel Bahnhof", "Hotel Alphubel", "Hotel Rhodania"}, {"Hotel Bellerive", "Hotel Sonne Zermatt", "Chesa Valese"}, {"The Omnia", "Mont Cervin Palace", "CERVO Mountain Resort"}}, {3, 3, 3}},
    {"Davos", {{"Hotel Edelweiss", "Hotel Alpina", ""}, {"Hotel Europe Davos", "Waldhotel Davos", ""}, {"Berghotel Schatzalp", "", ""}}, {2, 2, 1}},
    {"Grindelwald", {{"Hotel Hirschen", "Historic Hotel Steinbock", ""}, {"Eiger Mountain & Soul Resort", "Sunstar Hotel Grindelwald", ""}, {"BERGWELT GRINDELWALD | ALPINE DESIGN RESORT", "", ""}}, {2, 2, 1}},
    {"Andermatt", {{"Hotel Aurora", "Gasthaus Skiklub", ""}, {"Hotel 3 Könige & Post", "Hotel Crown", ""}, {"The Chedi Andermatt", "Radisson Blu Hotel Reussen", ""}}, {2, 2, 2}}
};
const PlaceHotels relaxation_hotels[MAX_PLACES] = {
    {"St. Moritz", {{"Hotel Piz St. Moritz", "Hotel Languard", "Youth Hostel St. Moritz"}, {"Hotel Steffani", "Hotel Hauser", "Hotel Waldhaus am See"}, {"Badrutt's Palace Hotel", "Kulm Hotel St. Moritz", "Suvretta House"}}, {3, 3, 3}},
    {"Bad Ragaz", {{"Sorell Hotel Tamina - Garni", "Garni Hotel Torkelbündte", "Palais Bad Ragaz"}, {"Hotel Schloss Ragaz", "Krone by b-smart", "Esos Hotel Quelle"}, {"Grand Resort Bad Ragaz", "Sorell Hotel Tamina", "Hotel Schloss Ragaz"}}, {3, 3, 3}},
    {"Lugano", {{"Hotel Pestalozzi Lugano", "Hotel Walter Au Lac", "Hotel Colibrì"}, {"LUGANODANTE - We like you", "Kurhaus Cademario Hotel & DOT SPA", "Villa Sassa Hotel, Residence & SPA"}, {"The View Lugano", "Grand Hotel Villa Castagnola", "Villa Principe Leopoldo"}}, {3, 3, 3}},
    {"Geneva", {{"Hotel de la Cigogne", "Hotel Cornavin", "Hotel Kipling Manotel"}, {"Hotel Bristol Geneva", "Hotel Rotary Geneva MGallery", "Hotel N'vY"}, {"Beau-Rivage Geneva", "Four Seasons Hotel des Bergues Geneva", "Mandarin Oriental Geneva"}}, {3, 3, 3}},
    {"Lenzerheide", {{"Youth Hostel Valbella-Lenzerheide", "Hotel Kurhaus", "Hotel Seehof Valbella"}, {"Hotel Lenzerhorn Spa & Wellness", "Hotel Schweizerhof Lenzerheide", "Hotel Dieschen"}, {"PRIVÀ Alpine Lodge", "Valbella Resort", "Hotel Guarda Val"}}, {3, 3, 3}}
};
const PlaceHotels culture_hotels[MAX_PLACES] = {
    {"Lucerne", {{"ibis budget Luzern City", "", ""}, {"ibis Styles Luzern City", "Hotel Alpina", "Holiday Inn Express Luzern – Kriens by IHG"}, {"Hotel Schweizerhof Luzern", "", ""}}, {1, 3, 1}},
    {"Bern", {{"Hotel Ambassador (fassbindhotels.ch)", "", ""}, {"Swissôtel Kursaal Berne", "Holiday Inn Bern – Westside by IHG", ""}, {"Hotel Bellevue Palace", "Hotel Schweizerhof Bern & Spa", ""}}, {1, 2, 2}},
    {"Geneva", {{"Lake Geneva Hotel", "B&B HOTEL Geneva Airport", "Hôtel St-Gervais"}, {"Hilton Geneva Hotel & Conference Centre", "", ""}, {"Four Seasons Hotel des Bergues Geneva", "Hotel d'Angleterre Geneva", "Beau-Rivage Genève"}}, {3, 1, 3}},
    {"Zurich", {{"City Home Zurich", "", ""}, {"ibis budget Zurich City West", "Mercure Zurich City", "The Home Hotel Zürich (Design Hotels)"}, {"The Dolder Grand", "La Réserve Eden au Lac Zurich", "Park Hyatt Zurich"}}, {1, 3, 3}},
    {"Appenzell", {{"City Home St. Gallen", "Hotel Weisses Kreuz", "Kränzlin"}, {"Hotel Hecht Appenzell", "Hotel Appenzell", ""}, {"Einstein St. Gallen", "", ""}}, {3, 2, 1}}
};
const PlaceHotels* get_place_hotels(const char* place_name, int category) {
    const PlaceHotels* hotels_array;
    switch(category) {
        case 1: hotels_array = adventure_hotels; break;
        case 2: hotels_array = relaxation_hotels; break;
        case 3: hotels_array = culture_hotels; break;
        default: return NULL;
    }
    for(int i = 0; i < MAX_PLACES; i++) {
        if(strcmp(hotels_array[i].place, place_name) == 0) {
            return &hotels_array[i];
        }
    }
    return NULL;
}
const PlaceHotels* get_category_hotels(int category) {
    switch(category) {
        case 1: return adventure_hotels;
        case 2: return relaxation_hotels;
        case 3: return culture_hotels;
        default: return NULL;
    }
}

// =============================================================================
// SEASONS IMPLEMENTATION ( 그대로 유지 )
// =============================================================================
const char summer_destinations[MAX_SEASONAL_PLACES][MAX_PLACE_NAME] = {
    "Interlaken", "Davos", "St. Moritz", "Geneva", "Appenzell",
    "Lucerne", "Lugano", "Lenzerheide", "Zermatt"
};
const char winter_destinations[7][MAX_PLACE_NAME] = {
    "Zermatt", "Davos", "St. Moritz", "Andermatt", "Lenzerheide", "Geneva", "Zurich"
};
const char spring_destinations[5][MAX_PLACE_NAME] = {
    "Bad Ragaz", "Bern", "Lucerne", "Geneva", "Zurich"
};
const char autumn_destinations[5][MAX_PLACE_NAME] = {
    "Bad Ragaz", "Bern", "Lenzerheide", "Lucerne", "Geneva"
};
const char (*get_seasonal_destinations(int season, int *count))[MAX_PLACE_NAME] {
    switch(season) {
        case 1: *count = 5; return spring_destinations;
        case 2: *count = MAX_SEASONAL_PLACES; return summer_destinations;
        case 3: *count = 5; return autumn_destinations;
        case 4: *count = 7; return winter_destinations;
        default: *count = 0; return NULL;
    }
}

// =============================================================================
// UTILITY FUNCTIONS FOR MAIN PROGRAM ( 그대로 유지 )
// =============================================================================
int recommend(const char category_places[][MAX_NAME_LENGTH], int cat_count,
              const char seasonal_places[][MAX_PLACE_NAME], int season_count,
              char recommended[][MAX_NAME_LENGTH]) {
    int rec_count = 0;
    if (category_places == NULL || seasonal_places == NULL) return 0;

    for(int i = 0; i < cat_count && strlen(category_places[i]) > 0 && rec_count < MAX_DESTINATIONS; i++) {
        for(int j = 0; j < season_count; j++) {
            if(strcmp(category_places[i], seasonal_places[j]) == 0) {
                int already_recommended = 0;
                for (int k=0; k < rec_count; ++k) {
                    if (strcmp(recommended[k], category_places[i]) == 0) {
                        already_recommended = 1;
                        break;
                    }
                }
                if (!already_recommended) {
                    strcpy(recommended[rec_count], category_places[i]);
                    rec_count++;
                }
                break;
            }
        }
    }
    return rec_count;
}


// =============================================================================
// HELPER FUNCTIONS FOR ROBUST INPUT ( 그대로 유지 )
// =============================================================================
int get_integer_input(const char *prompt, int min_val, int max_val) {
    char buffer[100];
    long value;
    char *endptr;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading input. Exiting.\n");
            exit(EXIT_FAILURE);
        }
        buffer[strcspn(buffer, "\n")] = 0;
        value = strtol(buffer, &endptr, 10);

        if (endptr == buffer) {
            printf("Invalid input. Please enter a number.\n");
        } else if (*endptr != '\0') {
            int all_whitespace = 1;
            char *temp = endptr;
            while(*temp) {
                if (!isspace((unsigned char)*temp)) {
                    all_whitespace = 0;
                    break;
                }
                temp++;
            }
            if (!all_whitespace) {
                 printf("Invalid input. Please enter only a number and no extra non-whitespace characters.\n");
                 continue;
            }
        }
        if (endptr != buffer && (*endptr == '\0' || isspace((unsigned char)*endptr))) { // Check if conversion happened and rest is whitespace or null
             if (value >= min_val && value <= max_val) {
                return (int)value;
            } else {
                printf("Input out of range. Please enter a number between %d and %d.\n", min_val, max_val);
            }
        } else if (endptr == buffer) {
            // Message already printed if no digits found
        }
    }
}

void get_date_input(const char *prompt_msg, int *month, int *day) {
    char buffer[100];
    int m, d;

    while (1) {
        printf("%s", prompt_msg);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error reading input. Exiting.\n");
            exit(EXIT_FAILURE);
        }
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (sscanf(buffer, "%d-%d", &m, &d) == 2) {
            char *ptr = buffer;
            while (*ptr && isdigit((unsigned char)*ptr)) ptr++;
            if (*ptr == '-') ptr++; else { printf("Invalid date format. Please use MM-DD.\n"); continue;}
            while (*ptr && isdigit((unsigned char)*ptr)) ptr++;
            
            int clean_end = 1;
            while(*ptr) {
                if(!isspace((unsigned char)*ptr)) {
                    clean_end = 0;
                    break;
                }
                ptr++;
            }

            if (clean_end) {
                if (m >= 1 && m <= 12 && d >= 1 && d <= 31) { 
                    *month = m;
                    *day = d;
                    return; 
                } else {
                    printf("Invalid date values. Month (1-12), Day (1-31).\n");
                }
            } else {
                printf("Invalid date format. Please use MM-DD and no extra characters.\n");
            }
        } else {
            printf("Invalid date format. Please use MM-DD.\n");
        }
    }
}


// =============================================================================
// MAIN PROGRAM (MODIFIED FOR BUDGET DISPLAY & VALUES)
// =============================================================================
int main() {
    int category_choice, num_travelers, budget_pref_choice;
    Date start_date, end_date;
    int start_month, start_day, end_month, end_day;
    char recommended_places[MAX_DESTINATIONS][MAX_NAME_LENGTH];
    for(int i=0; i < MAX_DESTINATIONS; ++i) recommended_places[i][0] = '\0';

    int rec_count = 0;
    int budget_chf_result[3]; 
    double budget_inr_result[3];

    printf("========================================\n");
    printf("Welcome to the Swiss Travel Planner!\n");
    printf("========================================\n\n");

    printf("We currently specialize in planning trips to Switzerland.\n");

    printf("\nWhat kind of trip are you looking for?\n");
    printf("1. Adventure\n");
    printf("2. Relaxation\n");
    printf("3. Culture Exploration\n");
    category_choice = get_integer_input("Enter your choice (1-3): ", 1, 3);

    const char (*selected_category_places)[MAX_NAME_LENGTH] = get_category(category_choice);
    if (selected_category_places == NULL) { 
        fprintf(stderr, "Error retrieving category destinations. Exiting.\n");
        return 1;
    }

    printf("\n--- Travel Dates ---\n");
    while (1) {
        get_date_input("Enter the start date of your vacation (MM-DD format): ", &start_month, &start_day);
        start_date = create_date(start_month, start_day);

        get_date_input("Enter the end date of your vacation (MM-DD format): ", &end_month, &end_day);
        end_date = create_date(end_month, end_day);

        if (compare_dates(start_date, end_date) && !(start_date.month == end_date.month && start_date.day == end_date.day)) { 
             printf("End date cannot be before the start date. Please re-enter.\n");
        } else if (start_date.month == end_date.month && start_date.day == end_date.day) {
             printf("Start and end dates cannot be the same for a meaningful trip. Please re-enter if you plan a multi-day trip.\n");
        }
        else {
            break; 
        }
    }

    int season = get_season(start_date, end_date);
    if (season == 0) {
        printf("Could not determine a clear season for the given dates, or your trip spans multiple seasons.\n");
        printf("For now, we will proceed by showing all places in your chosen category.\n");
        for (int i=0; i < MAX_DESTINATIONS; ++i) {
            if (strlen(selected_category_places[i]) > 0) {
                strcpy(recommended_places[rec_count++], selected_category_places[i]);
            } else {
                break; 
            }
        }
    } else {
        int seasonal_place_count;
        const char (*seasonal_destinations_list)[MAX_PLACE_NAME] = get_seasonal_destinations(season, &seasonal_place_count);
        if (seasonal_destinations_list == NULL) {
            fprintf(stderr, "Error retrieving seasonal destinations. Exiting.\n");
            return 1;
        }
        int actual_category_place_count = 0;
        for(int i=0; i<MAX_DESTINATIONS; ++i) {
            if(strlen(selected_category_places[i]) == 0) break;
            actual_category_place_count++;
        }
        rec_count = recommend(selected_category_places, actual_category_place_count, seasonal_destinations_list, seasonal_place_count, recommended_places);
    }

    printf("\n--- Recommended Places & Highlights ---\n");
    if (rec_count == 0) {
        printf("No places match both your chosen category and the season of travel.\n");
        printf("Consider adjusting your dates or category.\n");
    } else {
        for(int i = 0; i < rec_count; i++) {
            printf("%d. %s\n", i + 1, recommended_places[i]);
            const PlaceHighlights* current_highlights = get_place_highlights(recommended_places[i], category_choice);
            if (current_highlights != NULL && current_highlights->num_highlights > 0) {
                printf("\tHighlights: ");
                for(int k = 0; k < current_highlights->num_highlights; k++) {
                    if(strlen(current_highlights->highlights[k]) == 0) continue;
                    printf("%s", current_highlights->highlights[k]);
                    if(k < current_highlights->num_highlights - 1 && (k + 1 < MAX_HIGHLIGHTS_PER_PLACE) && strlen(current_highlights->highlights[k+1]) > 0) {
                        printf(", ");
                    }
                }
                printf("\n");
            } else {
                printf("\tHighlights: Not available.\n");
            }
        }
    }

    if (rec_count == 0) {
        printf("\nThank you for using our travel planner.\n");
        return 0;
    }

    char chosen_place_name[MAX_NAME_LENGTH];
    printf("\nWhich of these places would you like to get hotel information for?\n");
    int chosen_place_index = get_integer_input("Enter the number corresponding to your choice: ", 1, rec_count);
    strcpy(chosen_place_name, recommended_places[chosen_place_index - 1]);

    printf("\n--- Traveler & Budget Details ---\n");
    num_travelers = get_integer_input("How many people are traveling? (1-10): ", 1, 10);

    calculate_budget(num_travelers, budget_chf_result, budget_inr_result); 
    
    printf("\nWhat is your approximate budget PER DAY for %d person(s)? (1 CHF ~ %.2f INR based on current data)\n", num_travelers, CHF_TO_INR_RATE);
    printf("1. Minimal: Approx. CHF %d (approx. INR %.0f) per day\n", budget_chf_result[0], budget_inr_result[0]);
    printf("2. Mid-range: Approx. CHF %d (approx. INR %.0f) per day\n", budget_chf_result[1], budget_inr_result[1]);
    printf("3. Luxury: Approx. CHF %d (approx. INR %.0f) per day\n", budget_chf_result[2], budget_inr_result[2]);
    budget_pref_choice = get_integer_input("Enter your budget preference (1-3): ", 1, 3);


    const PlaceHotels* hotels_for_chosen_place = get_place_hotels(chosen_place_name, category_choice);
    printf("\n--- Hotel Options in %s (Budget: %s) ---\n",
        chosen_place_name,
        budget_pref_choice == 1 ? "Minimal" : (budget_pref_choice == 2 ? "Mid-range" : "Luxury")
    );

    if(hotels_for_chosen_place != NULL) {
        int budget_cat_index = budget_pref_choice - 1;
        int hotels_found_in_budget = 0;
        if (budget_cat_index >= 0 && budget_cat_index < MAX_BUDGETS && hotels_for_chosen_place->hotels_count[budget_cat_index] > 0) {
            for(int i = 0; i < hotels_for_chosen_place->hotels_count[budget_cat_index]; i++) {
                if (i >= MAX_HOTELS_PER_BUDGET) break;
                if(strlen(hotels_for_chosen_place->budget_hotels[budget_cat_index][i]) > 0) {
                    printf("%d. %s\n", hotels_found_in_budget + 1, hotels_for_chosen_place->budget_hotels[budget_cat_index][i]);
                    hotels_found_in_budget++;
                }
            }
        }
        if (hotels_found_in_budget == 0) {
             printf("No specific hotels listed for '%s' in the '%s' budget category in our current data.\n",
                    chosen_place_name,
                    budget_pref_choice == 1 ? "Minimal" : (budget_pref_choice == 2 ? "Mid-range" : "Luxury"));
        }
    } else {
        printf("No hotel information found for '%s' in our current data.\n", chosen_place_name);
    }

    printf("\n========================================\n");
    printf("Thank you for using our Swiss Travel Planner.\nWe hope you have a wonderful trip to %s!\n", chosen_place_name);
    printf("========================================\n");

    return 0;
}
#ifndef BUDGET_H
#define BUDGET_H

/*
Minimum Budget (₹6,500/day): Basic hostels, budget meals, public transport
Mid-Range Budget (₹30,000/day): 3-star hotels, moderate dining, comfortable travel
Luxury Budget (₹85,000/day): 5-star hotels, fine dining, premium experiences

Minimum Budget (₹6,500):
Accommodation (hostels/budget hotels): ₹1,800
Food (local/budget restaurants): ₹2,500
Local transportation: ₹1,500
Activities/sightseeing: ₹700

Mid-Range Budget (₹30,000):
Accommodation (3-star hotels): ₹10,000
Food (mid-range restaurants): ₹7,500
Local transportation: ₹3,000
Activities/sightseeing: ₹3,500
Shopping/miscellaneous: ₹6,000

Luxury Budget (₹85,000):
Accommodation (5-star hotels): ₹30,000
Food (fine dining): ₹15,000
Local transportation (private): ₹7,500
Activities/sightseeing (premium): ₹10,000
Shopping/miscellaneous: ₹22,500
*/

// Budget structure for different categories
typedef struct {
    int minimum;
    int mid_range;
    int luxury;
} BudgetRange;

// Global budget for one person
extern const BudgetRange one_person_budget;

// Function to calculate budget based on number of people
void calculate_budget(int num_people, int budget_result_chf[3], double budget_result_inr[3]);

#endif
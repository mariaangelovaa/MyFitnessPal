// CalorieCalculator.h
#ifndef CALORIE_CALCULATOR_H
#define CALORIE_CALCULATOR_H

#include "User.h"
#include "Macros.h"

class CalorieCalculator {
public:
    // Calculate BMR (Basal Metabolic Rate) for the user
    static float calculateBMR(const User& user);

    // Calculate total calorie expenditure based on activity level
    static float calculateTotalCalories(const User& user);

    // Calculate target calories based on the user's goal
    static float calculateTargetCalories(const User& user);

    // Calculate macros (protein, fat, carbs) based on target calories
    static Macros calculateMacros(const User& user, float totalCalories);
};

#endif // CALORIE_CALCULATOR_H

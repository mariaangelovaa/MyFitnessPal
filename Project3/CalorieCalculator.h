#ifndef CALORIE_CALCULATOR_H
#define CALORIE_CALCULATOR_H

#include "User.h"
#include "Macros.h"

float calculateBMR(const User& user);

float calculateTotalCalories(const User& user);

// Function to calculate target calories based on the user's goal
float calculateTargetCalories(const User& user);

Macros calculateMacros(const User& user, float totalCalories);

#endif 

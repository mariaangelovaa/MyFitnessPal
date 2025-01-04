#include "CalorieCalculator.h"
#include <iostream>
#include <string>

// Calculate BMR based on user data
float CalorieCalculator::calculateBMR(const User& user) {
    if (user.gender == "male") {
        return 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    else {
        return 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }
}

// Calculate total calories based on BMR and activity level
float CalorieCalculator::calculateTotalCalories(const User& user) {
    float bmr = calculateBMR(user);
    float activity_multiplier = 1.2;

    if (user.activity_level == "Light") {
        activity_multiplier = 1.375;
    }
    else if (user.activity_level == "Moderate") {
        activity_multiplier = 1.55;
    }
    else if (user.activity_level == "Active") {
        activity_multiplier = 1.725;
    }
    else if (user.activity_level == "Very Active") {
        activity_multiplier = 1.9;
    }

    return bmr * activity_multiplier;
}

// Calculate target calories based on user's goal (lose, gain, or maintain weight)
float CalorieCalculator::calculateTargetCalories(const User& user) {
    float totalCalories = calculateTotalCalories(user);

    if (user.goal == "Lose") {
        return totalCalories - 500; // For losing 0.5 kg per week
    }
    else if (user.goal == "Gain") {
        return totalCalories + 500; // For gaining 0.5 kg per week
    }
    else {
        return totalCalories; // For weight maintenance
    }
}

// Calculate macros (protein, fat, carbs) based on target calories and user goal
Macros CalorieCalculator::calculateMacros(const User& user, float totalCalories) {
    float protein, fat, carbs;

    if (user.goal == "Lose") {
        protein = totalCalories * 0.35 / 4;
        fat = totalCalories * 0.30 / 9;
        carbs = totalCalories * 0.35 / 4;
    }
    else if (user.goal == "Gain") {
        protein = totalCalories * 0.40 / 4;
        fat = totalCalories * 0.25 / 9;
        carbs = totalCalories * 0.35 / 4;
    }
    else {
        protein = totalCalories * 0.25 / 4;
        fat = totalCalories * 0.30 / 9;
        carbs = totalCalories * 0.45 / 4;
    }

    // Return the macros as a Macros object
    return Macros(protein, fat, carbs);
}

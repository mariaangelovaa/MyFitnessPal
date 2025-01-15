#include "CalorieCalculator.h"

float calculateBMR(const User& user) {
    if (user.gender == "male") {
        return 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
    }
    else {
        return 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
    }
}

float calculateTotalCalories(const User& user) {
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

float calculateTargetCalories(const User& user) {
    float totalCalories = calculateTotalCalories(user);

    if (user.goal == "Lose") {
        return totalCalories - user.kgToLose; // For losing 0.5 kg per week
    }
    else if (user.goal == "Gain") {
        return totalCalories + user.kgToGain; // For gaining weight
    }
    else {
        return totalCalories; // For weight maintenance
    }
}

Macros calculateMacros(const User& user, float totalCalories) {
    float protein, fat, carbs;

    // Calculate macros based on user's goal
    if (user.goal == "Lose") {
        protein = totalCalories * 0.35f / 4.0f;
        fat = totalCalories * 0.30f / 9.0f;
        carbs = totalCalories * 0.35f / 4.0f;
    }
    else if (user.goal == "Gain") {
        protein = totalCalories * 0.40f / 4.0f;
        fat = totalCalories * 0.25f / 9.0f;
        carbs = totalCalories * 0.35f / 4.0f;
    }
    else {
        protein = totalCalories * 0.25f / 4.0f;
        fat = totalCalories * 0.30f / 9.0f;
        carbs = totalCalories * 0.45f / 4.0f;
    }

    // Initialize a Macros struct and set the values
    Macros macros;
    initMacros(macros, protein, fat, carbs);

    // Return the macros
    return macros;
}

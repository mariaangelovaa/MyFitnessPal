#include "CalorieCalculator.h"

float calculateBMR(const User& user) {
    if (user.gender == "male") {
        return BMR_MALE_CONSTANT + (BMR_WEIGHT_COEFFICIENT_MALE * user.weight)
            + (BMR_HEIGHT_COEFFICIENT_MALE * user.height) - (BMR_AGE_COEFFICIENT_MALE * user.age);
    }
    else {
        return BMR_FEMALE_CONSTANT + (BMR_WEIGHT_COEFFICIENT_FEMALE * user.weight) 
            + (BMR_HEIGHT_COEFFICIENT_FEMALE * user.height) - (BMR_AGE_COEFFICIENT_FEMALE * user.age);
    }
}

float calculateTotalCalories(const User& user) {
    float bmr = calculateBMR(user);

    if (user.activity_level == "Light") {
        return ACTIVITY_MULTIPLIER_LIGHT * bmr;
    }
    else if (user.activity_level == "Moderate") {
        return ACTIVITY_MULTIPLIER_MODERATE * bmr;
    }
    else if (user.activity_level == "Active") {
        return ACTIVITY_MULTIPLIER_ACTIVE * bmr;
    }
    else if (user.activity_level == "Very Active") {
        return ACTIVITY_MULTIPLIER_VERY_ACTIVE * bmr;
    }

    return bmr * ACTIVITY_MULTIPLIER_DEFAULT;
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
        protein = totalCalories * CALORIES_MACRO_PROTEIN_LOSE / CALORIES_PER_GRAM_PROTEIN;
        fat = totalCalories * CALORIES_MACRO_FAT_LOSE / CALORIES_PER_GRAM_FAT;
        carbs = totalCalories * CALORIES_MACRO_CARBS_LOSE / CALORIES_PER_GRAM_CARBS;
    }
    else if (user.goal == "Gain") {
        protein = totalCalories * CALORIES_MACRO_PROTEIN_GAIN / CALORIES_PER_GRAM_PROTEIN;
        fat = totalCalories * CALORIES_MACRO_FAT_GAIN / CALORIES_PER_GRAM_FAT;
        carbs = totalCalories * CALORIES_MACRO_CARBS_GAIN / CALORIES_PER_GRAM_CARBS;
    }
    else {
        protein = totalCalories * CALORIES_MACRO_PROTEIN_MAINTENANCE / CALORIES_PER_GRAM_PROTEIN;
        fat = totalCalories * CALORIES_MACRO_FAT_MAINTENANCE / CALORIES_PER_GRAM_FAT;
        carbs = totalCalories * CALORIES_MACRO_CARBS_MAINTENANCE / CALORIES_PER_GRAM_CARBS;
    }

    // Initialize a Macros struct and set the values
    Macros macros;
    initMacros(macros, protein, fat, carbs);

    // Return the macros
    return macros;
}

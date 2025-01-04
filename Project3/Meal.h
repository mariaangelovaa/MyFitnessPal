#ifndef MEAL_H
#define MEAL_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime> // For ctime functions

class Meal {
public:
    std::string name;
    float calories;
    std::string date; // Date of the meal

    // Constructor to initialize the meal with name, calories, and date
    Meal(const std::string& name, float calories);

    // Function to add a meal to the file
    static void addMeal(const std::string& username, const Meal& meal, const std::string& filename);

    // Function to get total calories consumed by the user
    static float getTotalCalories(const std::string& username, const std::string& filename);

    // Function to get total calories for a specific date
    static float getTotalCaloriesForDate(const std::string& username, const std::string& date, const std::string& filename);

    // Function to delete meals by a specific date
    static void deleteMealsByDate(const std::string& username, const std::string& date, const std::string& filename);

    // Function to update a meal in the file
    static void updateMeal(const std::string& username, const Meal& newMeal, const std::string& filename);
};

#endif // MEAL_H

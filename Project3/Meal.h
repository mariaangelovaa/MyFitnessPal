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
    Meal(const std::string& name, float calories) : name(name), calories(calories) {
        // Get current date using ctime
        std::time_t t = std::time(nullptr); // Get current time
        std::tm* tm = std::localtime(&t); // Convert to local time

        // Format the date to YYYY-MM-DD
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm);
        date = buffer;  // Save the formatted date
    }

    // Function to add a meal to the file
    static void addMeal(const std::string& username, const Meal& meal, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << meal.name << " " << meal.calories << " " << meal.date << "\n";
        }
    }

    // Function to get total calories consumed by the user
    static float getTotalCalories(const std::string& username, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCalories = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name, date;
            float calories;

            ss >> storedUsername >> name >> calories >> date;

            if (storedUsername == username) {
                totalCalories += calories;
            }
        }

        return totalCalories;
    }

    // Function to get total calories for a specific date
    static float getTotalCaloriesForDate(const std::string& username, const std::string& date, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCalories = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name, mealDate;
            float calories;

            ss >> storedUsername >> name >> calories >> mealDate;

            if (storedUsername == username && mealDate == date) {
                totalCalories += calories;
            }
        }

        return totalCalories;
    }

    // Function to delete meals by a specific date
    static void deleteMealsByDate(const std::string& username, const std::string& date, const std::string& filename) {
        std::ifstream infile(filename);
        std::ofstream tempFile("temp_meals.txt");
        std::string line;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name, mealDate;
            float calories;

            ss >> storedUsername >> name >> calories >> mealDate;

            if (storedUsername == username && mealDate != date) {
                tempFile << line << "\n"; // Write all meals except the ones with the given date
            }
        }

        infile.close();
        tempFile.close();

        // Replace original file with the temp file
        std::remove(filename.c_str());
        std::rename("temp_meals.txt", filename.c_str());
    }

    // Function to update a meal in the file
    static void updateMeal(const std::string& username, const Meal& newMeal, const std::string& filename) {
        std::ifstream infile(filename);
        std::ofstream tempFile("temp_meals.txt");
        std::string line;
        bool updated = false;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name, date;
            float calories;

            ss >> storedUsername >> name >> calories >> date;

            if (storedUsername == username && date == newMeal.date && name == newMeal.name) {
                // Update the meal with the new data
                tempFile << username << " " << newMeal.name << " " << newMeal.calories << " " << newMeal.date << "\n";
                updated = true;
            }
            else {
                tempFile << line << "\n";
            }
        }

        infile.close();
        tempFile.close();

        if (!updated) {
            // If no update was made, add the new meal
            addMeal(username, newMeal, filename);
        }
        else {
            // Replace original file with the temp file
            std::remove(filename.c_str());
            std::rename("temp_meals.txt", filename.c_str());
        }
    }

};

#endif // MEAL_H

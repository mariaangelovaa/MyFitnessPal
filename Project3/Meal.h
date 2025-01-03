#ifndef MEAL_H
#define MEAL_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Meal {
public:
    std::string name;
    float calories;
    std::string date; // Date of the meal

    Meal(const std::string& name, float calories) : name(name), calories(calories) {
        // Use system command to get the date (works on Unix-like systems)
        char buffer[128];
#ifdef _WIN32  // For Windows
        FILE* fp = _popen("date /t", "r"); // Windows command to get date

#endif
        if (fp) {
            fgets(buffer, sizeof(buffer), fp);
            date = buffer;  // Save the date in YYYY-MM-DD format
            fclose(fp);
        }
    }

    static void addMeal(const std::string& username, const Meal& meal, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << meal.name << " " << meal.calories << " " << meal.date << "\n";
        }
    }

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

    // In Meal.h
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

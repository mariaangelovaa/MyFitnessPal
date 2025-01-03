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
#else  // For Linux or macOS
        FILE* fp = popen("date +%Y-%m-%d", "r"); // Unix/Linux/Mac command
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
};

#endif // MEAL_H

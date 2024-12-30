#ifndef MEAL_H
#define MEAL_H

#include <string>
#include <fstream>  // За файлови потоци
#include <sstream>  // За stringstream
#include <iostream>

class Meal {
public:
    std::string name;
    float calories; // Калории за едно хранене

    Meal(const std::string& name, float calories) : name(name), calories(calories) {}

    // Записване на храненето в файл
    static void addMeal(const std::string& username, const Meal& meal, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << meal.name << " " << meal.calories << "\n";
        }
    }

    // Прочитане на всички хранения от файл и изчисляване на общия калориен прием
    static float getTotalCalories(const std::string& username, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCalories = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name;
            float calories;

            ss >> storedUsername >> name >> calories;

            if (storedUsername == username) {
                totalCalories += calories;
            }
        }

        return totalCalories;
    }
};

#endif // MEAL_H

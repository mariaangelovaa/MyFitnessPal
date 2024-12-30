#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include <fstream>  // За файлови потоци
#include <sstream>  // За използване на stringstream
#include <iostream>

class Exercise {
public:
    std::string name;
    float caloriesBurned; // Калории, които са изгорени при тренировка

    Exercise(const std::string& name, float caloriesBurned) : name(name), caloriesBurned(caloriesBurned) {}

    // Записване на тренировката в файл
    static void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << exercise.name << " " << exercise.caloriesBurned << "\n";
        }
    }

    // Прочитане на всички тренировки от файл и изчисляване на общите изгорени калории
    static float getTotalCaloriesBurned(const std::string& username, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCaloriesBurned = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name;
            float caloriesBurned;

            ss >> storedUsername >> name >> caloriesBurned;

            if (storedUsername == username) {
                totalCaloriesBurned += caloriesBurned;
            }
        }

        return totalCaloriesBurned;
    }
};

#endif // EXERCISE_H

#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Exercise {
public:
    std::string name;
    float caloriesBurned;
    std::string date; // Date of the exercise

    Exercise(const std::string& name, float caloriesBurned) : name(name), caloriesBurned(caloriesBurned) {
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

    static void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << exercise.name << " " << exercise.caloriesBurned << " " << exercise.date << "\n";
        }
    }

    static float getTotalCaloriesBurned(const std::string& username, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCaloriesBurned = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name, date;
            float caloriesBurned;

            ss >> storedUsername >> name >> caloriesBurned >> date;

            if (storedUsername == username) {
                totalCaloriesBurned += caloriesBurned;
            }
        }

        return totalCaloriesBurned;
    }
};

#endif // EXERCISE_H

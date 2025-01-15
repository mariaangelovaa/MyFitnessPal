#define _CRT_SECURE_NO_WARNINGS
#include "Exercise.h"
#include <fstream>
#include <sstream>
#include <ctime>

void initExercise(Exercise& exercise, const std::string& name, float caloriesBurned) {
    exercise.name = name;
    exercise.caloriesBurned = caloriesBurned;

    // Get current date using ctime
    std::time_t t = std::time(nullptr); // Get current time
    std::tm* tm = std::localtime(&t); // Convert to local time

    // Format the date to DD.MM.YYYY
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", tm);
    exercise.date = buffer;  // Save the formatted date
}

void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename) {
    std::ofstream outfile(filename, std::ios::app);
    if (outfile.is_open()) {
        outfile << username << " " << exercise.name << " " << exercise.caloriesBurned << " " << exercise.date << "\n";
    }
}

float getTotalCaloriesBurned(const std::string& username, const std::string& filename) {
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

float getTotalCaloriesBurnedForDate(const std::string& username, const std::string& date, const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    float totalCaloriesBurned = 0;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, exerciseDate;
        float caloriesBurned;

        ss >> storedUsername >> name >> caloriesBurned >> exerciseDate;

        if (storedUsername == username && exerciseDate == date) {
            totalCaloriesBurned += caloriesBurned;
        }
    }

    return totalCaloriesBurned;
}

void deleteExercisesByDate(const std::string& username, const std::string& date, const std::string& filename) {
    std::ifstream infile(filename);
    std::ofstream tempFile("temp_exercises.txt");
    std::string line;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, exerciseDate;
        float caloriesBurned;

        ss >> storedUsername >> name >> caloriesBurned >> exerciseDate;

        if (storedUsername == username && exerciseDate != date) {
            tempFile << line << "\n"; // Write all exercises except the ones with the given date
        }
    }

    infile.close();
    tempFile.close();

    // Replace original file with the temp file
    std::remove(filename.c_str());
    std::rename("temp_exercises.txt", filename.c_str());
}

void updateExercise(const std::string& username, const Exercise& newExercise, const std::string& filename) {
    std::ifstream infile(filename);
    std::ofstream tempFile("temp_exercises.txt");
    std::string line;
    bool updated = false;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, date;
        float caloriesBurned;

        ss >> storedUsername >> name >> caloriesBurned >> date;

        if (storedUsername == username && date == newExercise.date && name == newExercise.name) {
            // Update the exercise with the new data
            tempFile << username << " " << newExercise.name << " " << newExercise.caloriesBurned << " " << newExercise.date << "\n";
            updated = true;
        }
        else {
            tempFile << line << "\n";
        }
    }

    infile.close();
    tempFile.close();

    if (!updated) {
        addExercise(username, newExercise, filename);
    }
    else {
        // Replace original file with the temp file
        std::remove(filename.c_str());
        std::rename("temp_exercises.txt", filename.c_str());
    }
}

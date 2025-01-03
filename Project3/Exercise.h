#ifndef EXERCISE_H
#define EXERCISE_H
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime> // For ctime functions

class Exercise {
public:
    std::string name;
    float caloriesBurned;
    std::string date; // Date of the exercise

    // Constructor to initialize the exercise with name, calories burned, and date
    Exercise(const std::string& name, float caloriesBurned) : name(name), caloriesBurned(caloriesBurned) {
        // Get current date using ctime
        std::time_t t = std::time(nullptr); // Get current time
        std::tm* tm = std::localtime(&t); // Convert to local time

        // Format the date to YYYY-MM-DD
        char buffer[11];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm);
        date = buffer;  // Save the formatted date
    }

    // Function to add an exercise to the file
    static void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << exercise.name << " " << exercise.caloriesBurned << " " << exercise.date << "\n";
        }
    }

    // Function to get total calories burned by the user
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

    // Function to get total calories burned for a specific date
    static float getTotalCaloriesBurnedForDate(const std::string& username, const std::string& date, const std::string& filename) {
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

    // Function to delete exercises by a specific date
    static void deleteExercisesByDate(const std::string& username, const std::string& date, const std::string& filename) {
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

    // Function to update an exercise in the file
    static void updateExercise(const std::string& username, const Exercise& newExercise, const std::string& filename) {
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
            // If no update was made, add the new exercise
            addExercise(username, newExercise, filename);
        }
        else {
            // Replace original file with the temp file
            std::remove(filename.c_str());
            std::rename("temp_exercises.txt", filename.c_str());
        }
    }
};

#endif // EXERCISE_H

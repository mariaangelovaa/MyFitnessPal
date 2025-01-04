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
    Exercise(const std::string& name, float caloriesBurned);

    // Function to add an exercise to the file
    static void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename);

    // Function to get total calories burned by the user
    static float getTotalCaloriesBurned(const std::string& username, const std::string& filename);

    // Function to get total calories burned for a specific date
    static float getTotalCaloriesBurnedForDate(const std::string& username, const std::string& date, const std::string& filename);

    // Function to delete exercises by a specific date
    static void deleteExercisesByDate(const std::string& username, const std::string& date, const std::string& filename);

    // Function to update an exercise in the file
    static void updateExercise(const std::string& username, const Exercise& newExercise, const std::string& filename);
};

#endif // EXERCISE_H

/**
*
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
*
* @author Maria Angelova
* @idnumber 4MI0600425
* @compiler VS
*
* header file for exercises
*
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime> // For ctime functions

// Structure to hold exercise information
struct Exercise {
    std::string name;
    float caloriesBurned;
    std::string date; // Date of the exercise
};

// Function to initialize an exercise
void initExercise(Exercise& exercise, const std::string& name, float caloriesBurned);

// Function to add an exercise to the file
void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename);

// Function to get total calories burned by the user
float getTotalCaloriesBurned(const std::string& username, const std::string& filename);

// Function to get total calories burned for a specific date
float getTotalCaloriesBurnedForDate(const std::string& username, const std::string& date, const std::string& filename);

// Function to delete exercises by a specific date
void deleteExercisesByDate(const std::string& username, const std::string& date, const std::string& filename);

// Function to update an exercise in the file
void updateExercise(const std::string& username, const Exercise& newExercise, const std::string& filename);

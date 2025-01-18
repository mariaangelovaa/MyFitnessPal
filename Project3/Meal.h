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
* header file for meals
*
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

struct Meal {
    std::string name;
    float calories;
    std::string date;
};

void initMeal(Meal& meal, const std::string& name, float calories);

void addMeal(const std::string& username, const Meal& meal, const std::string& filename);

float getTotalCalories(const std::string& username, const std::string& filename);

float getTotalCaloriesForDate(const std::string& username, const std::string& date, const std::string& filename);

void deleteMealsByDate(const std::string& username, const std::string& date, const std::string& filename);

void updateMeal(const std::string& username, const Meal& newMeal, const std::string& filename);

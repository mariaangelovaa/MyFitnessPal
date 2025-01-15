#ifndef MEAL_H
#define MEAL_H
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

#endif

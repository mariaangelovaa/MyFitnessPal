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
* header file for Calorie Calculations
*
*/

#pragma once

#include "User.h"
#include "Macros.h"

float calculateBMR(const User& user);

float calculateTotalCalories(const User& user);

// Function to calculate target calories based on the user's goal
float calculateTargetCalories(const User& user);

Macros calculateMacros(const User& user, float totalCalories);

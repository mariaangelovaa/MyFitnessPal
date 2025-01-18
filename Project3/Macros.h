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
* header file for macros
*
*/

#pragma once

#include <iostream>
#include "Constants.h"

// Structure to hold macros
struct Macros {
    float protein;
    float fat;
    float carbs;
};

void initMacros(Macros& macros, float protein = 0.0f, float fat = 0.0f, float carbs = 0.0f);

void displayMacros(const Macros& macros);
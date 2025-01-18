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
* file for macros
*
*/

#include "Macros.h"

void initMacros(Macros& macros, float protein, float fat, float carbs) {
    macros.protein = protein;
    macros.fat = fat;
    macros.carbs = carbs;
}

void displayMacros(const Macros& macros) {
    std::cout << "Protein: " << macros.protein << " g\n";
    std::cout << "Fat: " << macros.fat << " g\n";
    std::cout << "Carbs: " << macros.carbs << " g\n";
}

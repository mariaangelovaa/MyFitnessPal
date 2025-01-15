#ifndef MACROS_H
#define MACROS_H

#include <iostream>

// Structure to hold macros
struct Macros {
    float protein;
    float fat;
    float carbs;
};

void initMacros(Macros& macros, float protein = 0.0f, float fat = 0.0f, float carbs = 0.0f);

void displayMacros(const Macros& macros);

#endif 

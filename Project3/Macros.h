#ifndef MACROS_H
#define MACROS_H

#include <iostream>

class Macros {
public:
    float protein;
    float fat;
    float carbs;

    // Constructor to initialize the macros
    Macros(float protein = 0.0f, float fat = 0.0f, float carbs = 0.0f);

    // Function to display the macros
    void display() const;
};

#endif // MACROS_H

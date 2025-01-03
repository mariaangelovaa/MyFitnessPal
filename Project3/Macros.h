#include <iostream>

// Macros class to store protein, fat, and carbs
class Macros {
public:
    float protein;
    float fat;
    float carbs;

    // Constructor to initialize the macros
    Macros(float protein = 0.0f, float fat = 0.0f, float carbs = 0.0f)
        : protein(protein), fat(fat), carbs(carbs) {}

    // Function to display the macros
    void display() const {
        std::cout << "Protein: " << protein << " g\n";
        std::cout << "Fat: " << fat << " g\n";
        std::cout << "Carbs: " << carbs << " g\n";
    }
};
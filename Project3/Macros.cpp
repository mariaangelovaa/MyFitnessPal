#include "Macros.h"

// Constructor to initialize the macros
Macros::Macros(float protein, float fat, float carbs)
    : protein(protein), fat(fat), carbs(carbs) {}

// Function to display the macros
void Macros::display() const {
    std::cout << "Protein: " << protein << " g\n";
    std::cout << "Fat: " << fat << " g\n";
    std::cout << "Carbs: " << carbs << " g\n";
}

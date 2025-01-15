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

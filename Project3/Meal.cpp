#include "Meal.h"

// Constructor to initialize the meal with name, calories, and date
Meal::Meal(const std::string& name, float calories) : name(name), calories(calories) {
    // Get current date using ctime
    std::time_t t = std::time(nullptr); // Get current time
    std::tm* tm = std::localtime(&t);   // Convert to local time

    // Format the date to dd.mm.yyyy
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", tm);  // Format as dd.mm.yyyy
    date = buffer;  // Save the formatted date
}

// Function to add a meal to the file
void Meal::addMeal(const std::string& username, const Meal& meal, const std::string& filename) {
    std::ofstream outfile(filename, std::ios::app);
    if (outfile.is_open()) {
        outfile << username << " " << meal.name << " " << meal.calories << " " << meal.date << "\n";
    }
}

// Function to get total calories consumed by the user
float Meal::getTotalCalories(const std::string& username, const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    float totalCalories = 0;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, date;
        float calories;

        ss >> storedUsername >> name >> calories >> date;

        if (storedUsername == username) {
            totalCalories += calories;
        }
    }

    return totalCalories;
}

// Function to get total calories for a specific date
float Meal::getTotalCaloriesForDate(const std::string& username, const std::string& date, const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    float totalCalories = 0;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, mealDate;
        float calories;

        ss >> storedUsername >> name >> calories >> mealDate;

        if (storedUsername == username && mealDate == date) {
            totalCalories += calories;
        }
    }

    return totalCalories;
}

// Function to delete meals by a specific date
void Meal::deleteMealsByDate(const std::string& username, const std::string& date, const std::string& filename) {
    std::ifstream infile(filename);
    std::ofstream tempFile("temp_meals.txt");
    std::string line;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, mealDate;
        float calories;

        ss >> storedUsername >> name >> calories >> mealDate;

        if (storedUsername == username && mealDate != date) {
            tempFile << line << "\n"; // Write all meals except the ones with the given date
        }
    }

    infile.close();
    tempFile.close();

    // Replace original file with the temp file
    std::remove(filename.c_str());
    std::rename("temp_meals.txt", filename.c_str());
}

// Function to update a meal in the file
void Meal::updateMeal(const std::string& username, const Meal& newMeal, const std::string& filename) {
    std::ifstream infile(filename);
    std::ofstream tempFile("temp_meals.txt");
    std::string line;
    bool updated = false;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, date;
        float calories;

        ss >> storedUsername >> name >> calories >> date;

        if (storedUsername == username && date == newMeal.date && name == newMeal.name) {
            // Update the meal with the new data
            tempFile << username << " " << newMeal.name << " " << newMeal.calories << " " << newMeal.date << "\n";
            updated = true;
        }
        else {
            tempFile << line << "\n";
        }
    }

    infile.close();
    tempFile.close();

    if (!updated) {
        // If no update was made, add the new meal
        addMeal(username, newMeal, filename);
    }
    else {
        // Replace original file with the temp file
        std::remove(filename.c_str());
        std::rename("temp_meals.txt", filename.c_str());
    }
}

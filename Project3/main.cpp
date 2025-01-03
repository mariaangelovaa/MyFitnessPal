#include <iostream>
#include <string>
#include "User.h"
#include "Exercise.h"
#include "Meal.h"
#include "CalorieCalculator.h"

User loggedInUser;

// Function to handle user registration
void handleRegister(const std::string& filename) {
    std::string username, password, gender, activity, goal, accountType;
    int age;
    float height, weight;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    std::cout << "Enter gender (M/F): ";
    std::cin >> gender;

    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "Enter height (cm): ";
    std::cin >> height;

    std::cout << "Enter weight (kg): ";
    std::cin >> weight;

    std::cout << "Enter activity level (Sedentary/Light/Moderate/Active/Very Active): ";
    std::cin >> activity;

    std::cout << "Enter goal (Lose/Maintain/Gain): ";
    std::cin >> goal;

    std::cout << "Select account type (Standard/Premium): ";
    std::cin >> accountType;

    User newUser(username, password, gender, age, height, weight, activity, goal, accountType);
    if (User::registerUser(filename, newUser)) {
        std::cout << "Registration successful!\n";
    }
}

// Function to handle user login
bool handleLogin(const std::string& filename, std::string& username) {
    std::string password;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (User::loginUser(filename, username, password)) {
        loggedInUser = User::getUserFromFile(filename, username);
        std::cout << "Login successful!\n";
        return true;
    }
    else {
        std::cout << "Invalid username or password.\n";
        return false;
    }
}

// Function to show the main menu
void showMainMenu() {
    std::cout << "\nWelcome to the Calorie Tracker!\n";
    std::cout << "1. View Daily Report\n";
    std::cout << "2. Add Meal\n";
    std::cout << "3. Add Exercise\n";
    std::cout << "4. View recommended daily calorie intake\n";
    std::cout << "5. Logout\n";
    std::cout << "Please select an option: ";
}

// Function to view the daily report
void viewDailyReport(const std::string& username) {
    // Calculate total calories from meals and exercises
    float totalCalories = Meal::getTotalCalories(username, "meals.txt");
    float totalCaloriesBurned = Exercise::getTotalCaloriesBurned(username, "exercises.txt");

    std::cout << "\nDaily Report for " << username << ":\n";
    std::cout << "Total Calories Consumed: " << totalCalories << " kcal\n";
    std::cout << "Total Calories Burned: " << totalCaloriesBurned << " kcal\n";
    std::cout << "Net Calories: " << (totalCalories - totalCaloriesBurned) << " kcal\n";
}

// Function to add a meal
void addMeal(const std::string& username) {
    std::string name;
    float calories;

    std::cout << "Enter meal name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter calories: ";
    std::cin >> calories;

    Meal meal(name, calories);
    Meal::addMeal(username, meal, "meals.txt");
    std::cout << "Meal added successfully!\n";
}

// Function to add an exercise
void addExercise(const std::string& username) {
    std::string name;
    float caloriesBurned;

    std::cout << "Enter exercise name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter calories burned: ";
    std::cin >> caloriesBurned;

    Exercise exercise(name, caloriesBurned);
    Exercise::addExercise(username, exercise, "exercises.txt");
    std::cout << "Exercise added successfully!\n";
}

// Function to view recommended daily calorie intake
void viewRecommendedCalorieIntake(const std::string& username) {
    float targetCalories = CalorieCalculator::calculateTargetCalories(loggedInUser);

    // Output the result
    std::cout << "\nYour recommended daily calorie intake is: " << targetCalories << " kcal\n";
}

int main() {
    std::string filename = "users.txt";
    std::string username;
    bool loggedIn = false;
    int choice;

    // Show login or register options until user logs in
    while (!loggedIn) {
        std::cout << "Welcome to the Calorie Tracker! Please select an option:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Please select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            handleRegister(filename);
            break;
        case 2:
            loggedIn = handleLogin(filename, username);
            break;
        case 3:
            std::cout << "Exiting program.\n";
            return 0;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    // Once logged in, show the main menu
    while (loggedIn) {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewDailyReport(username);
            break;
        case 2:
            addMeal(username);
            break;
        case 3:
            addExercise(username);
            break;
        case 4:
            viewRecommendedCalorieIntake(username);
            break;
        case 5:
            std::cout << "Logged out successfully.\n";
            loggedIn = false;  // Reset login status to false
            break;  // Return to the login/register menu
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    // This ensures that after logging out, we return to the login/register menu
    return main();  // Recursively call main to restart the loop
}

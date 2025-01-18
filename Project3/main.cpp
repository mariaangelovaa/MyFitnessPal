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
* main file
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Exercise.h"
#include "Meal.h"
#include "CalorieCalculator.h"

User loggedInUser;

void handleRegister(const std::string& filename) {
    std::string username, password, gender, activity, goal, accountType;
    int age;
    float height, weight, kgToLose = 0, kgToGain = 0;
    User newUser;

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

    if (goal == "Lose") {
        std::cout << "How much weight per week do you intend to lose? (in kg): ";
        std::cin >> kgToLose;
    }
    else if (goal == "Gain") {
        std::cout << "How much weight per week do you intend to gain? (in kg): ";
        std::cin >> kgToGain;
    }
    // If goal is "Maintain", kgToLose and kgToGain stay 0 (default)

    std::cout << "Select account type (Standard/Premium): ";
    std::cin >> accountType;

    initUser(newUser, username, password, gender, age, height, weight, activity, goal, kgToLose, kgToGain, accountType);
    if (registerUser(filename, newUser)) {
        std::cout << "Registration successful!\n";
    }
}

bool handleLogin(const std::string& filename, std::string& username) {
    std::string password;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (loginUser(filename, username, password)) {
        loggedInUser = getUserFromFile(filename, username);
        std::cout << "Login successful!\n";
        return true;
    }
    else {
        std::cout << "Invalid username or password.\n";
        return false;
    }
}

void showMainMenu() {
    std::cout << "\n---------------------------------\n";
    std::cout << "\nPlease choose an option: \n";
    std::cout << "1. View Daily Report for Today\n";
    std::cout << "2. View Daily Report for a Specific Date\n";
    std::cout << "3. Add Meal\n";
    std::cout << "4. Add Exercise\n";
    std::cout << "5. View recommended daily calorie intake\n";
    std::cout << "6. Delete Meals by Date\n";
    std::cout << "7. Delete Exercises by Date\n";
    std::cout << "8. Update Meal for Today\n";
    std::cout << "9. Update Exercise for Today\n";
    std::cout << "10. Update Physical info\n";
    std::cout << "11. Logout\n";
    std::cout << "12. Show Macros for Premium User\n";
    std::cout << "Please select an option: ";
}

void viewDailyReport(const std::string& username, const std::string& date) {
    // Calculate total calories from meals and exercises for the given date
    float totalCalories = getTotalCaloriesForDate(username, date, "meals.txt");
    float totalCaloriesBurned = getTotalCaloriesBurnedForDate(username, date, "exercises.txt");

    std::cout << "\nDaily Report for " << username << " on " << date << ":\n";
    std::cout << "Total Calories Consumed: " << totalCalories << " kcal\n";
    std::cout << "Total Calories Burned: " << totalCaloriesBurned << " kcal\n";
    std::cout << "Net Calories: " << (totalCalories - totalCaloriesBurned) << " kcal\n";

    // Display all meals for the given date
    std::cout << "\nMeals for " << date << ":\n";
    std::ifstream mealFile("meals.txt");
    std::string line;
    bool mealFound = false;
    while (std::getline(mealFile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, mealDate;
        float calories;

        ss >> storedUsername >> name >> calories >> mealDate;

        if (storedUsername == username && mealDate == date) {
            std::cout << "Meal: " << name << " | Calories: " << calories << " kcal\n";
            mealFound = true;
        }
    }

    if (!mealFound) {
        std::cout << "No meals recorded for this date.\n";
    }

    mealFile.close();

    // Display all exercises for the given date
    std::cout << "\nExercises for " << date << ":\n";
    std::ifstream exerciseFile("exercises.txt");
    bool exerciseFound = false;
    while (std::getline(exerciseFile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, name, exerciseDate;
        float caloriesBurned;

        ss >> storedUsername >> name >> caloriesBurned >> exerciseDate;

        if (storedUsername == username && exerciseDate == date) {
            std::cout << "Exercise: " << name << " | Calories burned: " << caloriesBurned << " kcal\n";
            exerciseFound = true;
        }
    }

    if (!exerciseFound) {
        std::cout << "No exercises recorded for this date.\n";
    }

    exerciseFile.close();
}

void addMeal(const std::string& username) {
    std::string name;
    float calories;
    Meal meal;

    std::cout << "Enter meal name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter calories: ";
    std::cin >> calories;

    initMeal(meal, name, calories);
    addMeal(username, meal, "meals.txt");
    std::cout << "Meal added successfully!\n";
}

void addExercise(const std::string& username) {
    std::string name;
    float caloriesBurned;
    Exercise exercise;

    std::cout << "Enter exercise name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter calories burned: ";
    std::cin >> caloriesBurned;

    initExercise(exercise, name, caloriesBurned);
    addExercise(username, exercise, "exercises.txt");
    std::cout << "Exercise added successfully!\n";
}

void viewRecommendedCalorieIntake(const std::string& username) {
    float targetCalories = calculateTargetCalories(loggedInUser);

    // Output the result
    std::cout << "\nYour recommended daily calorie intake is: " << targetCalories << " kcal\n";
}

std::string getTodayDate() {
    // Get current time
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);

    // Format the date to dd.mm.yyyy
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", tm);  // Format as dd.mm.yyyy
    return std::string(buffer);
}

// Function to display macros for premium users
void showMacrosForPremiumUser(const User& user) {
    if (user.account_type == "Premium") {
        float totalCalories = calculateTargetCalories(user);
        Macros macros = calculateMacros(user, totalCalories);

        std::cout << "\nYour macronutrients based on recommended daily calories:\n";
        std::cout << "Protein: " << macros.protein << "g\n";
        std::cout << "Fat: " << macros.fat << "g\n";
        std::cout << "Carbs: " << macros.carbs << "g\n";
    }
    else {
        std::cout << "This functionality is available only for Premium users.\n";
    }
}

int main() {
    std::string filename = "users.txt";
    std::string username;
    bool loggedIn = false;
    int choice;

    // Show login or register options until user logs in
    while (!loggedIn) {
        std::cout << "Welcome to the MariaFitnessPal app! Please select an option:\n";
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
        Exercise exercise;
        Meal meal;

        showMainMenu();
        std::string todayDate = getTodayDate();

        std::cin >> choice;
        switch (choice) {
        case 1:
            viewDailyReport(username, todayDate);
            break;
        case 2: {
            std::string date;
            std::cout << "Enter date (DD.MM.YYYY) to view the report: ";
            std::cin >> date;
            viewDailyReport(username, date);  // Call the new version of viewDailyReport with a specific date
            break;
        }
        case 3:
            addMeal(username);
            break;
        case 4:
            addExercise(username);
            break;
        case 5:
            viewRecommendedCalorieIntake(username);
            break;
        case 6: {
            std::string date;
            std::cout << "Enter date to delete meals (DD.MM.YYYY): ";
            std::cin >> date;
            deleteMealsByDate(username, date, "meals.txt");
            std::cout << "Meals for " << date << " deleted successfully.\n";
            break;
        }
        case 7: {
            std::string date;
            std::cout << "Enter date to delete exercises (DD.MM.YYYY): ";
            std::cin >> date;
            deleteExercisesByDate(username, date, "exercises.txt");
            std::cout << "Exercises for " << date << " deleted successfully.\n";
            break;
        }
        case 8: {
            std::string name;
            float calories;
            std::cout << "Enter meal name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new calories: ";
            std::cin >> calories;
            initMeal(meal, name, calories);
            updateMeal(username, meal, "meals.txt");
            std::cout << "Meal updated successfully!\n";
            break;
        }
        case 9: {
            std::string name;
            float caloriesBurned;
            std::cout << "Enter exercise name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new calories burned: ";
            std::cin >> caloriesBurned;
            initExercise(exercise, name, caloriesBurned);
            updateExercise(username, exercise, "exercises.txt");
            std::cout << "Exercise updated successfully!\n";
            break;
        }
        case 10: {
            updateUserPhysicalInfo("users.txt", username);  // Update user physical info
            loggedInUser = getUserFromFile(filename, username);
            break;
        }
        case 11:
            std::cout << "Logged out successfully.\n";
            loggedIn = false;  // Reset login status to false
            break;  // Return to the login/register menu
        case 12:
            showMacrosForPremiumUser(loggedInUser);
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    // This ensures that after logging out, we return to the login/register menu
    return main();
}
